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
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float lastX = 400, lastY = 300;
bool firstMouse = true;
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
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
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture myTex1(GL_TEXTURE_2D, "awesomeface.png");
	myTex1.wrap(GL_REPEAT, GL_REPEAT);
	myTex1.filter(GL_LINEAR, GL_LINEAR);


	myShader.use();
	myShader.setInt("myTexture1", 0);

	while (!glfwWindowShouldClose(window))
	{
		float curTime = glfwGetTime();
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//激活纹理单元： 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(myTex1.Type, myTex1.ID);

		myShader.use();//激活着色器程序
		//变换：
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = myCamera.GetViewMatrix();
		projection = glm::perspective(glm::radians(myCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		myShader.setMat4("view", glm::value_ptr(view));
		myShader.setMat4("projection", glm::value_ptr(projection));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//myShader.setMat4("model", glm::value_ptr(model));
		Chunk chunk;
		int x = 0, y = 0, z = 0;//block position in chunk	

		for (int i = 0; i < chunk.width; i++) {//z axis
			for (int j = 0; j < chunk.width; j++) {//y axis
				x = (int)(PerlinNoise(x, y + x, z + x)) % chunk.height;
				for (int k = 0; k < x + chunk.baseHeight; k++) {//1-4,x axis,height
					/*if (k == 0 || k == x+chunk.baseHeight || j == 0 || i == chunk.width) {
						glCullFace(GL_BACK);
					}
					else glCullFace(GL_FRONT_AND_BACK);*/
					glBindVertexArray(VAO);
					glDrawArrays(GL_TRIANGLES, 0, 36);
					model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));//height,x
					myShader.setMat4("model", glm::value_ptr(model));
				}
				model = glm::translate(model, glm::vec3((x + chunk.baseHeight)*1.0f, 1.0f, 0.0f));//y axis
				y++;
			}
			model = glm::translate(model, glm::vec3(0.0f, -chunk.width*1.0f, 1.0f));//z axis
			z++;
			y -= chunk.width;
		}
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = lastX - xpos;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	myCamera.ProcessMouseMovement(xoffset, yoffset, true);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}