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
#include"plantGenerator.h"
#include"Camera.h"

/*
	世界坐标系统：
	整个MC世界统一成一个三维坐标（和openGL的世界坐标不同
	设置每个方块为一个单独的坐标值；

	block是方块类，包含方块相关的定义和属性，以及和方块类型相关的材质（暂时不可实例化）；

	chunk是地图存储和渲染的基本单位；

	Map类控制地图生成，世界坐标和chunk存储坐标的转换；
	后续应该要独立出来一个地图生成类的部分（多个类）

	openGL和世界坐标的对应：一个方块 1:1
	y 对应 y
	z 对应 x

	使用摄像机所在的位置来判定需要加载的方块，加载摄像机周围对应的13组方块（暂定）

	后期需要使用openGL的缓冲区来实现加速

 */

class Map
{
private:
	std::vector<Chunk*> chunks;

	unsigned int VBO, VAO;
	Shader* myShader;
	Camera* myCamera;

	const static int sandheight = 20;

	int chunkSize;//amount of chunks in map

	int currentChunkMinX;
	int currentChunkMaxX;
	int currentChunkMinY;
	int currentChunkMaxY;

	// 用来尝试地形生成的私有函数，后续进一步重构应该要拆除
	// 可见方块判别算法
	bool isVisible(int index,int x, int y, int z);

	int generateHeight(double x, double y, double interval);
	Block::blockType generateBlockType(int x, int y, int z, int h);
	void generateBlock(int index);

	// 坐标转换系列

	// 通过世界坐标获取 chunk 下标
	int getBlockIndex(int x, int y);

public:
	Map(Camera* myCamera);
	~Map();

	// 在主函数刷新中需要调用的唯一一个函数，用来渲染地图
	void renderMap();

	// 当摄像机改变位置或者放置砖块后调用
	void updateMap();

	// 可以改用下面两个
	//void renderBlock(std::vector<operateBlock*> extraBlocks);//add blocks
	//void destroyBlock(std::vector<operateBlock*> delBlocks);//delete blocks
	
	// 将mc世界坐标转换为chunk存储坐标，然后操作方块
	// 操作方块的时候用
	void setBlock(int x, int y, int z, Block::blockType type);
	Block::blockType getBlockType(int x, int y, int z);

	// 预留接口，还没想好名字
	// 通过摄像机和方块的交线判断删除方块；没参数
	// 通过摄像机和方块的交线判断添加方块；没参数
	// 或者可以合并到一起
};

#endif 