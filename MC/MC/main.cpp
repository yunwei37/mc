#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Camera.h"
#include"Chunk.h"
#include"particleGenerator.h"
#include"stb_image.h"
#include"Block.h"
#include<time.h>
#include<vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Map.h"
#include "Player.h"
#include "Text.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
extern const unsigned int SCR_WIDTH = 800;
extern const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float lastX = 400, lastY = 300;
bool firstMouse = true;
Camera myCamera(glm::vec3(10.0f,28.0f,12.0f)/*(3.0f, 48.0f, 25.0f)*/, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,0.0f);
Map* myMap;
operateBlock changeBlock;
Player myPlayer(&myCamera);
int state;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Minecraft", NULL, NULL);
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
	/*Shader partShader("particles_vs.txt", "particles_fs.txt");
	Texture partTex(GL_TEXTURE_2D, "blocks/dirt.png");
	blockParticles = new ParticleGen(partShader, partTex, 10);*/
	state = 0;
	while (!glfwWindowShouldClose(window))
	{
		if (state == 0)
		{
			// Set OpenGL options
			glEnable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			// Check and call events
			glfwPollEvents();
			// Clear the colorbuffer
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Text text;
			glfwSwapBuffers(window);
//			processInput(window);
			if (state == 0 && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				state = 1;
				glDisable(GL_BLEND);
				glDisable(GL_CULL_FACE);
				glEnable(GL_DEPTH_TEST);//开启深度测试
				glEnable(GL_CULL_FACE);//面剔除
				myMap = new Map(&myCamera);
				Block::loadTextures();
			}
		}
		else //start the game
		{
			float curTime = glfwGetTime();
			deltaTime = curTime - lastFrame;
			lastFrame = curTime;
			processInput(window);
			glClearColor(91.0f / 255.0f, 206.0f/255.0f, 1.0f, 1.0f);//background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			myMap->renderMap(&changeBlock);//draw map
			changeBlock.init();
			// 交换缓冲并查询IO事件：
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
	}
	delete myMap;

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (state == 0 && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		state = 1;
	}
	else if (state == 1)
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
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			myPlayer.exchangeHandBlock();//空格换防止方块的类型，bug
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		myMap->limitCamera();
		myMap->updateMap();
	}
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{//screen origin(0,0): 左上角
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
	if (state == 1) {
		//double cursor_x = 0, cursor_y = 0;
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {//press 
			/*cout << "left press " << endl;
			glfwGetCursorPos(window, &cursor_x, &cursor_y);
			cout << cursor_x << "," << cursor_y << endl;*/
			//place a block
			myPlayer.getPlacingPos(changeBlock.mapCoord);//get placing world position
			changeBlock.type = myPlayer.inHand;
		}
		else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {

			/*double cursor_x = 0, cursor_y = 0;
			glfwGetCursorPos(window, &cursor_x, &cursor_y);
			cout << cursor_x << "," << cursor_y << endl;*/
			//destroy a block:
			changeBlock.type = Block::Air;
			myPlayer.getPlacingPos(changeBlock.mapCoord);//get player's world position
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}

