#pragma once
#ifndef  BLOCK_H
#define BLOCK_H
#include <string>
#include <glm/glm.hpp>
class Block
{
public:

	enum blockType { //Block的类型 
		Air = 0,//空气
		Water = 1,//水
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

};

class operateBlock//the placed block's information
{
public:
	void init();
	operateBlock();
	int mapCoord[3];
	Block::blockType type;
};

#endif // 
