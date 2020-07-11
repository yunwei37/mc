#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Shader.h"
#include"Camera.h"
#include"Texture.h"
//#include"Chunk.h"
//#include"PerlinNoise.h"
#include"stb_image.h"
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
Camera myCamera(glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(0.0f, 1.0f, 0.0f),90.0f,0.0f);
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
//	glDepthFunc(GL_LESS);		// Set to always pass the depth test(same effect as glDisable(GL_DEPTH_TEST))
	glEnable(GL_BLEND);		// 为了渲染出不同的透明度级别，我们需要开启混合(Blending)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	Shader myShader("test_vs.txt", "test_fs.txt");
	float vertices[] = {
		-0.1f, -0.1f, -0.1f,  0.0f, 0.0f,
		 0.1f,  0.1f, -0.1f,  2.0f, 2.0f,
		 0.1f, -0.1f, -0.1f,  2.0f, 0.0f,
		 0.1f,  0.1f, -0.1f,  2.0f, 2.0f,
		-0.1f, -0.1f, -0.1f,  0.0f, 0.0f,
		-0.1f,  0.1f, -0.1f,  0.0f, 2.0f,

		-0.1f, -0.1f,  0.1f,  0.0f, 0.0f,
		 0.1f, -0.1f,  0.1f,  2.0f, 0.0f,
		 0.1f,  0.1f,  0.1f,  2.0f, 2.0f,
		 0.1f,  0.1f,  0.1f,  2.0f, 2.0f,
		-0.1f,  0.1f,  0.1f,  0.0f, 2.0f,
		-0.1f, -0.1f,  0.1f,  0.0f, 0.0f,

		-0.1f,  0.1f,  0.1f,  2.0f, 0.0f,
		-0.1f,  0.1f, -0.1f,  2.0f, 2.0f,
		-0.1f, -0.1f, -0.1f,  0.0f, 2.0f,
		-0.1f, -0.1f, -0.1f,  0.0f, 2.0f,
		-0.1f, -0.1f,  0.1f,  0.0f, 0.0f,
		-0.1f,  0.1f,  0.1f,  2.0f, 0.0f,

		 0.1f,  0.1f,  0.1f,  2.0f, 0.0f,
		 0.1f, -0.1f, -0.1f,  0.0f, 2.0f,
		 0.1f,  0.1f, -0.1f,  2.0f, 2.0f,
		 0.1f, -0.1f, -0.1f,  0.0f, 2.0f,
		 0.1f,  0.1f,  0.1f,  2.0f, 0.0f,
		 0.1f, -0.1f,  0.1f,  0.0f, 0.0f,

		-0.1f, -0.1f, -0.1f,  0.0f, 1.0f,
		 0.1f, -0.1f, -0.1f,  1.0f, 1.0f,
		 0.1f, -0.1f,  0.1f,  1.0f, 0.0f,
		 0.1f, -0.1f,  0.1f,  1.0f, 0.0f,
		-0.1f, -0.1f,  0.1f,  0.0f, 0.0f,
		-0.1f, -0.1f, -0.1f,  0.0f, 1.0f,

		-0.1f,  0.1f, -0.1f,  0.0f, 0.5f,
		 0.1f,  0.1f,  0.1f,  1.0f, 0.0f,
		 0.1f,  0.1f, -0.1f,  1.0f, 1.0f,
		 0.1f,  0.1f,  0.1f,  1.0f, 0.0f,
		-0.1f,  0.1f, -0.1f,  0.0f, 1.0f,
		-0.1f,  0.1f,  0.1f,  0.0f, 0.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0*sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
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
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		myShader.setMat4("model", glm::value_ptr(model));
		
		for (int i = 0; i < 10; i++) {
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.2f));
			myShader.setMat4("model", glm::value_ptr(model));	
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			for (int j = 0; j < 10; j++) {
				model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
				myShader.setMat4("model", glm::value_ptr(model));
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
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
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);
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
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	myCamera.ProcessMouseMovement(xoffset, yoffset, true);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}