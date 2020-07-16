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
#include"PerlinNoise.h"
#include "Shader.h"
#include "config.h"

class Chunk {
public:
	//const static int width = 16; //每个Chunk的长宽Size 
	//const static int height = 64; //每个Chunk的高度 
	//int seed; //随机种子 
	bool isLoad;

	Chunk(int x,int y);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[CHUNKWIDTH][CHUNKWIDTH][CHUNKHEIGHT];	// Chunk的网格
	bool isRender[CHUNKWIDTH][CHUNKWIDTH][CHUNKHEIGHT];			// 标记当前方块层是否有被渲染
	//int visibleHeight[ width + 2 ][ width + 2 ];	// 随机生成的可见地表高度 
	bool layerRender[CHUNKHEIGHT];
	//chunk在map中的坐标：
	int x;
	int y;

	void updateRenderInformation();

};
#endif 