#include "Map.h"

Map::Map(int chunkSize)
{
	for (int i = 0; i < chunkSize; ++i) {
		chunks.push_back(Chunk());
	}
}

void Map::renderMap()
{

}
