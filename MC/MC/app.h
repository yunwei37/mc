#pragma once
#ifndef APP_H_
#define APP_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"view/Camera.h"
#include"model/Chunk.h"
#include"view/particleGenerator.h"
#include"view/stb_image.h"
#include"model/Block.h"
#include<time.h>
#include<vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "viewmodel/Map.h"
#include "model/Player.h"
#include "view/Text.h"


class app
{
private:
	Camera* myCamera;
	Map* myMap;
	operateBlock changeBlock;
	Player *myPlayer;
	int state;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:
	app();
};

#endif