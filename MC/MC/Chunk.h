#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 64
#include<list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Block.h"
#include"PerlinNoise.h"
#include "Shader.h"

class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	int width; //每个Chunk的长宽Size 
	int height; //每个Chunk的高度 
	//int seed; //随机种子 
	bool isLoad;//true,loaded; false,not loaded
	
	//float frequency = 0.025;  //噪音频率（噪音采样时会用到） 
	//float amplitude = 1; //噪音振幅（噪音采样时会用到）
	//void buildChunk();
	Chunk(int x,int y, int width, int height);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_HEIGHT]; //Chunk的网格
	bool isRender[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_HEIGHT];
	int visibleHeight[CHUNK_WIDTH][CHUNK_WIDTH]; //随机生成的可见地表高度 
	//chunk在map中的坐标：
	int x;
	int y;

private:
	int generateHeight(double x, double y);
	Block::blockType generateBlockType(int x, int y, int z, int h);
	//BlockType[,,] map; 
	//Mesh chunkMesh; //存储着此Chunk内的所有Block信息 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
	bool isVisible(int x, int y, int z);
};
#endif 