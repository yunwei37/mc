#pragma once
#ifndef STRUCTBUILDER_H
#define STRUCTBUILDER_H
#include<vector>
#include "Chunk.h"
#include "Block.h"

class StructureBuilder {
public:
	void build(Chunk &chunk);
	void addY(int x, int z, int yStart, int height, Block::blockType type);//add blocks in Y axis
	void addX(int xStart, int xEnd, int y, int z, Block::blockType type);//add blocks in X axis
	void addZ(int zStart, int zEnd, int x, int y, Block::blockType type);//add blocks in Z axis
	void addXZ(int y, int xStart, int xEnd, int zStart, int zEnd, Block::blockType type);//add blocks in XZ plane
	void addBlock(int x, int y, int z, Block::blockType type);//add blocks

private:
	struct Block1 {
		Block1(Block::blockType type, int x, int y, int z) : Type(type), x(x), y(y), z(z) { }
		Block::blockType Type;
		int x, y, z;
	};
	std::vector<Block1> m_blocks;
};
	

#endif // !STRUCTBUILDER_H