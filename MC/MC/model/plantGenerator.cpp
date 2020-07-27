#include"plantGenerator.h"
#include"StructureBuilder.h"
#include<time.h>
#include<stdlib.h>
void makePalmTree(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand(seed + clock());
	int height = rand() % 6 + 4;//range 7-9
	//int height = 7;//range 7-9
	for (int h = height; h > height - 3 && h > 2; --h) {
		int diameter = rand() % 1 + 9 / h;//range 1 - 2
		for (int yLeaf = -diameter; yLeaf <= diameter; yLeaf++) {
			for (int xLeaf = -diameter; xLeaf <= diameter; xLeaf++) {
				if (xLeaf != x && yLeaf != y) {
					builder.addBlock(xLeaf + x, y + yLeaf, z + h, Block::Leaf);
				}
			}
		}
	}

	builder.addBlock(x, y, z + height + 1, Block::Leaf);
	builder.addZ(z, z + height, x, y, Block::Bark);
	builder.build(chunk);
}

void makeCactus(Chunk& chunk, int seed, int x, int y, int z)
{
	srand(seed);
	int choice = rand() % 6;
	if (choice > 4) {
		cactus2(chunk, seed, x, y, z);
	}
	else {
		cactus1(chunk, seed, x, y, z);
	}
}

void cactus1(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	builder.addZ(z, z + rand() % 3 + 1, x, y, Block::Cactus);
	builder.build(chunk);
}

void cactus2(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	int height = rand() % 3 + 5;//range 6 - 8
	builder.addZ(z, z + height, x, y, Block::Cactus);

	int stem = height / 2;
	builder.addX(x - 2, x + 2, y, z + height - 2, Block::Cactus);
	
	builder.addBlock(x, y + 1, z + height - 1, Block::Cactus);
	builder.addBlock(x, y - 1, z + height - 1, Block::Cactus);
	builder.build(chunk);
}