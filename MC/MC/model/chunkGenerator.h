#pragma once
#ifndef CHUNK_GE_
#define CHUNK_GE_
#include "../viewmodel/Chunk.h"
#include "plantGenerator.h"
#include "Block.h"

class chunkGenerator
{
private:
	// 用来尝试地形生成的私有函数，后续进一步重构应该要拆除
	// 可见方块判别算法
	static bool isVisible(Chunk& chunk, int x, int y, int z);

	static int generateHeight(double x, double y, double interval);
	static Block::blockType generateBlockType(int x, int y, int z, int h);

	const static int sandheight = 23;
	const static int waterheight = 20;

	static int seed;

public:
	static void generateBlock(Chunk& chunk);
};

#endif