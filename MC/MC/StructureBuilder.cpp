#include"StructureBuilder.h"

void StructureBuilder::build(Chunk &chunk)
{
	for (auto &block : m_blocks) {
		//chunk.setBlock(block.x, block.y, block.z, block.Type);
	}
}
void StructureBuilder::addY(int x, int z, int yStart, int height, blockType type)
{
	for (int i = 0; i < height; i++) {
		addBlock(x, yStart + i, z, type);
	}
}
void StructureBuilder::addX(int xStart, int xEnd, int y, int z, blockType type)
{
	for (int i = xStart; i <= xEnd; i++) {
		addBlock(i, y, z, type);
	}
}
void StructureBuilder::addZ(int zStart, int zEnd, int x, int y, blockType type)
{
	for (int i = zStart; i <= zEnd; i++) {
		addBlock(x, y, i, type);
	}
}
void StructureBuilder::addXZ(int y, int xStart, int xEnd, int zStart, int zEnd, blockType type)
{
	for (int i = xStart; i <= xEnd; i++) {
		for (int j = zStart; j <= zEnd; j++) {
			addBlock(i, y, j, type);
		}
	}
}
void StructureBuilder::addBlock(int x, int y, int z, blockType type)
{
	m_blocks.emplace_back(type, x, y, z);//==push_back, add to m_blocks
}