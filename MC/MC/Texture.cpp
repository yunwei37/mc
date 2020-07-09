#include"Texture.h"
#include<iostream>
Texture::Texture(GLenum type, const std::string &dataPath) :Type(type) {
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	stbi_set_flip_vertically_on_load(true);
	int height, width, colorChal;
	GLenum format;
	unsigned char *data = stbi_load(dataPath.c_str(), &width, &height, &colorChal, 0);
	format = (colorChal == 3) ? GL_RGB : GL_RGBA;
	if (data) {
		glTexImage2D(Type, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(Type);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void Texture::wrap(GLenum sWrap, GLenum tWrap)
{//wrapping only 2D, "s axis wrapping pattern, t axis wrapping pattern"
	glTexParameteri(Type, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(Type, GL_TEXTURE_WRAP_T, tWrap);
	/*if(Type==GL_TEXTURE_3D)
		glTexParameteri(Type, GL_TEXTURE_WRAP_T, rWrap);*/
}
void Texture::filter(GLenum mFilter, GLenum MFilter)
{//filtering, "minify filtering pattern, magnify filtering pattern"
	glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, mFilter);
	glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, MFilter);
}