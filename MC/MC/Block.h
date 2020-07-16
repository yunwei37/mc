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
		Cactus = 9,//仙人掌
		Cloud = 10,//云朵
	};

	static std::vector<Texture> textures;
    const static float vertices[];
	const static size_t vsize;

	static int loadTextures();

};
struct operateBlock//the placed block's information
{
	int mapCoord[2];
	int chunkCoord[2];
	Block::blockType type;
	operateBlock() {
		type = Block::Air;
		mapCoord[0] = 0;
		mapCoord[1] = 0;
		chunkCoord[0] = 0;
		chunkCoord[1] = 0;
	}
};

#endif // 
