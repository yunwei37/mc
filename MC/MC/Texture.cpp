#include "Texture.h"
#include <iostream>

Texture::Texture(GLenum type, const std::string& dataPath) {
	init(type, dataPath);
}
void Texture::init(GLenum type, const std::string& dataPath) {
	Type = type;
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	stbi_set_flip_vertically_on_load(true);
	int height, width, colorChal;
	GLenum format;
	unsigned char* data = stbi_load(dataPath.c_str(), &width, &height, &colorChal, 0);
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

Texture::Texture(std::vector<std::string> faces)
{
	ID = loadCubemap(faces);
	Type = GL_TEXTURE_CUBE_MAP;
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

unsigned int Texture::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GLenum format;
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data
			);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}