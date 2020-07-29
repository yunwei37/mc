
#include "app.h"

extern const unsigned int SCR_WIDTH = 800;
extern const unsigned int SCR_HEIGHT = 600;

double App::deltaTime = 0.0f; // 当前帧与上一帧的时间差
double App::lastFrame = 0.0f; // 上一帧的时间
double App::lastX = 400, App::lastY = 300;
bool App::firstMouse = true;
int App::state = 0;

Camera* App::myCamera = NULL;
Map* App::myMap = NULL;
operateBlock App::changeBlock;
Player* App::myPlayer = NULL;
GLFWwindow* App::window = NULL;

int App::createApp()
{	
	
	myCamera = new Camera(glm::vec3(10.0f, 28.0f, 12.0f)/*(3.0f, 48.0f, 25.0f)*/, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
	myPlayer = new Player();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MineCraft", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, &App::framebuffer_size_callback);
	glfwSetCursorPosCallback(window, &App::mouse_move_callback);
	glfwSetScrollCallback(window, &App::scroll_callback);
	glfwSetMouseButtonCallback(window, &App::mouse_click_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	return 0;
}

int App::run()
{
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
				myMap = new Map(myCamera);
				Map::loadTextures();
			}
		}
		else //start the game
		{
			double curTime = glfwGetTime();
			deltaTime = curTime - lastFrame;
			lastFrame = curTime;
			processInput(window);
			glClearColor(91.0f / 255.0f, 206.0f / 255.0f, 1.0f, 1.0f);//background
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
void App::processInput(GLFWwindow* window)
{
	if (state == 0 && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		state = 1;
	}
	else if (state == 1)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(LEFT, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(UP, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			myCamera->ProcessKeyboard(DOWN, (float)deltaTime);
			myMap->updateMap();
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			myPlayer->inHand = Block::Soil;//换放置方块的类型:泥土
			std::cout << "in hand: Soil" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			myPlayer->inHand = Block::Stone;//换放置方块的类型:石头
			std::cout << "in hand: Stone" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			myPlayer->inHand = Block::StondBrick;//换放置方块的类型：砖块
			std::cout << "in hand: Stone brick" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
			myPlayer->inHand = Block::Sand;//换放置方块的类型：沙块
			std::cout << "in hand: Sand" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			myPlayer->inHand = Block::Bark;//换放置方块的类型：木块
			std::cout << "in hand: Bark" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
			myPlayer->inHand = Block::Cactus;//换放置方块的类型：仙人掌
			std::cout << "in hand: Cactus" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void App::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{//screen origin(0,0): 左上角
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	myCamera->ProcessMouseMovement((float)xoffset, (float)yoffset, true);
}

void App::mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (state == 1) {
		//double cursor_x = 0, cursor_y = 0;
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {//press 
			/*cout << "left press " << endl;
			glfwGetCursorPos(window, &cursor_x, &cursor_y);
			cout << cursor_x << "," << cursor_y << endl;*/
			//place a block
			myCamera->getWorldPos(changeBlock.mapCoord);//get placing world position
			changeBlock.type = myPlayer->inHand;
		}
		else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {

			/*double cursor_x = 0, cursor_y = 0;
			glfwGetCursorPos(window, &cursor_x, &cursor_y);
			cout << cursor_x << "," << cursor_y << endl;*/
			//destroy a block:
			changeBlock.type = Block::Air;
			myCamera->getWorldPos(changeBlock.mapCoord);//get player's world position
		}
	}
}

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera->ProcessMouseScroll((float)yoffset);
}

App::App()
{
	if (App::createApp() == -1) {
		exit(-1);
	}
}

App::~App()
{
}

