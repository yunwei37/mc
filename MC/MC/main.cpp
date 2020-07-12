#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Shader.h"
#include"Camera.h"
#include"Texture.h"
#include"Chunk.h"
#include"PerlinNoise.h"
#include"stb_image.h"
#include<time.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void renderChunk(Chunk* chunk, unsigned int VAO, Shader* myShader, Texture* myTex2);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float lastX = 400, lastY = 300;
bool firstMouse = true;
clock_t lastPress = 0;
int seqPress = 0;
Camera myCamera(glm::vec3(-15.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);//开启深度测试
	glEnable(GL_CULL_FACE);//面剔除
	Shader myShader("test_vs.txt", "test_fs.txt");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Block::vsize, Block::vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	vector<std::string> faces
	{
		"blocks/grass_side.png",
		"blocks/grass.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png"
	};
	Texture myTex2(faces);

	myShader.use();
	myShader.setInt("myTexture1", 0);

	while (!glfwWindowShouldClose(window))
	{
		float curTime = glfwGetTime();
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;
		processInput(window);

		Chunk chunk;
		renderChunk(&chunk, VAO, &myShader, &myTex2);

		// 交换缓冲并查询IO事件：
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);


	glfwTerminate();
	return 0;
}

void renderChunk(Chunk* chunk, unsigned int VAO, Shader* myShader, Texture* myTex2) {

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();//激活着色器程序
	//变换：
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = myCamera.GetViewMatrix();
	projection = glm::perspective(glm::radians(myCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader->setMat4("view", glm::value_ptr(view));
	myShader->setMat4("projection", glm::value_ptr(projection));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//myShader.setMat4("model", glm::value_ptr(model));

	//激活纹理单元： 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(myTex2->Type, myTex2->ID);

	int z = 0, x = 0, y = 0;//block position in chunk	

	for (int i = 0; i < chunk->width; i++) {//z axis
		for (int j = 0; j < chunk->width; j++) {//y axis
			z = (int)((PerlinNoise2D(x * 0.3, y * 0.3) + 1) * 10);
			for (int k = 0; k < z + chunk->baseHeight; k++) {//1-4,x axis,height
				/*if (k == 0 || k == x+chunk.baseHeight || j == 0 || i == chunk.width) {
					glCullFace(GL_BACK);
				}
				else glCullFace(GL_FRONT_AND_BACK);*/
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));//height,x
				myShader->setMat4("model", glm::value_ptr(model));
			}
			model = glm::translate(model, glm::vec3((z + chunk->baseHeight) * 1.0f, 1.0f, 0.0f));//y axis
			x++;
		}
		model = glm::translate(model, glm::vec3(0.0f, -chunk->width * 1.0f, 1.0f));//z axis
		y++;
		x -= chunk->width;
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	myCamera.ProcessMouseMovement(xoffset, yoffset, true);
}
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {//press 
		if ((double)((clock() - lastPress) / CLOCKS_PER_SEC) < 0.1) {//multi press
			seqPress++;
			cout << "multi press " << seqPress << endl;
			if (seqPress == 6) {
				//block break
				seqPress = 0;
			}
		}
		else {//short press
			seqPress = 0;
			cout << "short press " << endl;
			//place block
		}
		lastPress = clock();
	}
	/*else if (action = GLFW_RELEASE) {
		lastPress = clock();
		if ((double)((clock() - lastPress) / CLOCKS_PER_SEC) > 5) {
			cout << "long press " << endl;
		}
		else cout << "short press " << endl;
	}*/
	//else if (action == GLFW_REPEAT) {//long press
	//	cout << "long press" << endl;
	//}
	return;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}