#pragma once
#ifndef  BLOCK_H
#define BLOCK_H
#include <map>
#include <string>

class Block
{
public:
	static std::map<std::string, unsigned int> Textures;
    const static float vertices[];
	const static size_t vsize;

	static int loadTextures();
};
#endif // 

