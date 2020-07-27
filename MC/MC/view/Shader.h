#pragma once
#ifndef SHADER_H
#define SHADER_H
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);//构建shader
	Shader() {}
	void use();//激活shader
	//uniform功能函数：
	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;
	void setMat4(const string& name, float value[])const;
	void set4fv(const string& name, float value[])const;
	void set3fv(const string& name, float value[])const;
private:
	void checkCompileErrors(unsigned int shader, string type);
};
#endif // !SHADER_H

