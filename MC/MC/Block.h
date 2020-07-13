#pragma once
#ifndef  BLOCK_H
#define BLOCK_H
#include <string>
#include "Texture.h"

class Block
{
public:

	enum blockType { //Block的类型 
		Air = 0,//空气
		Water =1,//水
		Soil = 2,//泥土
		Stone = 3,//石
		Grass = 4,//草皮
		Sand = 5,//沙子
		StondBrick = 6,//石砖
		Leaf = 7,//树叶
		Bark = 8,//树皮
		Cactus = 9//仙人掌
	};

	static std::vector<Texture> textures;
    const static float vertices[];
	const static size_t vsize;

	static int loadTextures();

};
#endif // 

