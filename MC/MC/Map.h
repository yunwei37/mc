#pragma once
#ifndef MAP_H
#define MAP_H

#include <map>
#include <vector>
#include <string>
#include "Chunk.h"

class Map
{
private:
	std::vector<Chunk> chunks;
public:
	Map(int chunkSize);
	void renderMap();
};

#endif 