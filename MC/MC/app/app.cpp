#include "app.h"

App::App()
{
	if ((window = ViewModel::createViewModel()) == NULL) {
		exit(-1);
	}
	glfwSetFramebufferSizeCallback(window, &ViewModel::framebuffer_size_callback);
	glfwSetCursorPosCallback(window, &ViewModel::mouse_move_callback);
	glfwSetScrollCallback(window, &ViewModel::scroll_callback);
	glfwSetMouseButtonCallback(window, &ViewModel::mouse_click_callback);
}

App::~App()
{

}

int App::run()
{	
	return ViewModel::run();
}
