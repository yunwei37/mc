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
enum blockType { //Block的类型 
	Air=0,//空气
	Soil = 1,//泥土
	Stone = 2,//碎石
	Water = 3,//水
	Grass = 4,//草皮
	Sand = 5,//沙子
	Leaf = 6,//树叶
	Bark = 7,//树皮
	Cactus = 8//仙人掌
};//存储着世界中所有的Chunk 
class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	int width = 32; //每个Chunk的长宽Size 
	int height = 3; //每个Chunk的高度 
	int seed; //随机种子 
	float baseHeight = 2; //最小生成高度 
	bool isLoad;//true,loaded; false,not loaded
	//float frequency = 0.025;  //噪音频率（噪音采样时会用到） 
	//float amplitude = 1; //噪音振幅（噪音采样时会用到）

	int generateHeight(double x, double y, double z);
	blockType generateBlockType(double Pos[3]);
	//void buildChunk();
//private:
//	BlockType[,,] map; //Chunk的网格
	//Mesh chunkMesh; //存储着此Chunk内的所有Block信息 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
};
#endif 