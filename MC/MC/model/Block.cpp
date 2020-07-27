#include "Block.h"

operateBlock::operateBlock()
{
	this->init();
}
void operateBlock::init()
{
	type = Block::Air;
	mapCoord[0] = -1;
	mapCoord[1] = -1;
	mapCoord[2] = -1;
}