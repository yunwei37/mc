#include"plantGenerator.h"
#include"StructureBuilder.h"
#include<time.h>
#include<stdlib.h>
void makePalmTree(Chunk &chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	int height = rand() % 3 + 7;//range 7-9
	int diameter = rand() % 3 + 4;//range 4 - 6
	for (int xLeaf = -diameter; xLeaf < diameter; xLeaf++) {
		builder.addBlock(xLeaf + x, y + height, z, Block::Leaf);
	}
	for (int zLeaf = -diameter; zLeaf < diameter; zLeaf++) {
		builder.addBlock(x, y + height, zLeaf + z, Block::Leaf);
	}
	builder.addBlock(x, y + height - 1, z + diameter, Block::Leaf);
	builder.addBlock(x, y + height - 1, z - diameter, Block::Leaf);
	builder.addBlock(x + diameter, y + height - 1, z, Block::Leaf);
	builder.addBlock(x - diameter, y + height - 1, z, Block::Leaf);
	builder.addBlock(x, y + height + 1, z, Block::Leaf);
	builder.addY(x, z, y, height, Block::Bark);
	builder.build(chunk);
}
void makeCactus(Chunk &chunk, int seed, int x, int y, int z)
{
	srand(seed);
	int choice = rand() & 0x01;
	switch (choice) {
	case 0:
		cactus1(chunk, seed, x, y, z);
		break;
	case 1:
		cactus2(chunk, seed, x, y, z);
		break;
	default:break;
	}
}
void cactus1(Chunk &chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	builder.addY(x, z, y, (rand()&0x03)+4, Block::Cactus);//range 4-7
	builder.build(chunk);
}
void cactus2(Chunk &chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	int height = rand() % 3 + 6;//range 6 - 8
	builder.addY(x, z, y, height, Block::Cactus);

	int stem = height / 2;
	builder.addX(x - 2, x + 2, stem + y, z, Block::Cactus);
	builder.addBlock(x - 2, stem + y + 1, z, Block::Cactus);
	builder.addBlock(x - 2, stem + y + 2, z, Block::Cactus);
	builder.addBlock(x + 2, stem + y + 1, z, Block::Cactus);
	builder.build(chunk);
}