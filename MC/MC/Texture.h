#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<string>
#include<glad/glad.h>
#include"stb_image.h"
class Texture {//only 2D
public:
	unsigned int ID;
	GLenum Type;
	Texture(GLenum type, const std::string &dataPath);//ctor
	void wrap(GLenum sWrap, GLenum tWrap);//wrapping only 2D, "s axis wrapping pattern, t axis wrapping pattern"
	void filter(GLenum mFilter, GLenum MFilter);//filtering, "minify filtering pattern, magnify filtering pattern"
};
#endif