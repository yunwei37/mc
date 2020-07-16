#pragma once

#ifndef MAPGenerator_H
#define MAPGenerator_H

#include "StructureBuilder.h"
#include "Chunk.h"
#include "config.h"

class MapGenerator
{
public:
	static void generateMap(Chunk* chunks[CHUNKSIZE][CHUNKSIZE], int startX, int startY);

private:

	const static int sandheight = 23;
	const static int waterheight = 20;

	const static int mapWidth = CHUNKWIDTH * CHUNKSIZE;

	static int heightMap[mapWidth][mapWidth];

	static int generateHeight(double x, double y, double interval);
	static Block::blockType generateBlockType(int z, int h);
	static void generateBlock(Chunk* c);

	// 可见方块判别算法
	bool isVisible(Chunk* c, int i, int j, int k);

	static void makePalmTree(Chunk& chunk, int seed, int x, int y, int z);//generate palm tree
	static void makeCactus(Chunk& chunk, int seed, int x, int y, int z);//generate cactus

	static void cactus1(Chunk& chunk, int seed, int x, int y, int z);//generate cactus1
	static void cactus2(Chunk& chunk, int seed, int x, int y, int z);//generate cactus2
};

#endif
