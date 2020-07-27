#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include<list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Block.h"
#include "PerlinNoise.h"
#include "../view/Shader.h"

class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	const static int width = 32; //每个Chunk的长宽Size 
	const static int height = 64; //每个Chunk的高度 
	//int seed; //随机种子 
	bool isLoad;//true,loaded; false,not loaded

	//float frequency = 0.025;  //噪音频率（噪音采样时会用到） 
	//float amplitude = 1; //噪音振幅（噪音采样时会用到）
	//void buildChunk();
	Chunk(int x, int y);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[width][width][height]; //Chunk的网格
	bool isRender[width][width][height];
	int visibleHeight[width + 2][width + 2]; //随机生成的可见地表高度 
	//chunk在map中的坐标：
	int x;
	int y;

private:
	//BlockType[,,] map; 
	//Mesh chunkMesh; //存储着此Chunk内的所有Block信息 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
};
#endif 