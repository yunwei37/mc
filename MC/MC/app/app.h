#pragma once
#ifndef APP_H_
#define APP_H_

#include "..\viewmodel\viewmodel.h"

class App
{
public:
	App();
	~App();
	int run();
private:
	GLFWwindow* window;
};

#endif
