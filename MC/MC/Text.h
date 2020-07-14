#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"stb_image.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Shader.h"
#include <map>

const GLuint WIDTH = 800, HEIGHT = 600;
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};



class Text {
public:
	Text();
	void RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	std::map<GLchar, Character> Characters;
	GLuint VAO;
	GLuint VBO;
};

#endif