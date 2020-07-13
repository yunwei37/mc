#pragma once
#ifndef MAP_H
#define MAP_H

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
	std::vector<Chunk> chunks;

	unsigned int VBO, VAO;
	Shader* myShader;
	Camera* myCamera;

public:
	Map(Camera* myCamera);
	~Map();
	void renderMap();
};

#endif 