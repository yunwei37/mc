#pragma once
#ifndef MAP_H
#define MAP_H
#define MAP_SIZE 9
#include <map>
#include <vector>
#include <string>
#include "Chunk.h"
#include"Shader.h"
#include"PerlinNoise.h"
#include"Camera.h"

class Map
{
private:
	std::vector<Chunk*> chunks;

	unsigned int VBO, VAO;
	Shader* myShader;
	Camera* myCamera;

	int chunkSize;//amount of chunks in map

public:
	Map(Camera* myCamera, int chunkSize);
	~Map();
	void renderMap();
	void renderBlock(std::vector<operateBlock*> extraBlocks);//add blocks
	void destroyBlock(std::vector<operateBlock*> delBlocks);//delete blocks
};

#endif 