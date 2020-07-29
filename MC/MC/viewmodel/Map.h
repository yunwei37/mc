#pragma once
#ifndef MAP_H
#define MAP_H
#define MAP_SIZE 9
#include <map>
#include <vector>
#include <string>
//#include "../view/particleGenerator.h"
#include "../view/resource_manager.h"
#include "Chunk.h"
#include "../view/Shader.h"
#include "../model/PerlinNoise.h"
#include "../model/plantGenerator.h"
#include "../model/chunkGenerator.h"
#include "../view/Camera.h"

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

	int chunkSize;//amount of chunks in map

	int currentChunkMinX;
	int currentChunkMaxX;
	int currentChunkMinY;
	int currentChunkMaxY;

	int startPosX;
	int startPosY;


	// 坐标转换系列

	// 通过block的世界坐标获取 chunk 下标
	int getBlockIndex(int x, int y);

public:
	Map(Camera* myCamera);
	~Map();

	// 在主函数刷新中需要调用的唯一一个函数，用来渲染地图
	void renderMap(operateBlock* changeBlock);

	// 当摄像机改变位置或者放置砖块后调用
	void updateMap();
	void limitCamera();//控制摄像机不会穿透表层

	// 加载纹理
	static int loadTextures();
	static std::vector<Texture> textures;
private:
	// 将mc世界坐标转换为chunk存储坐标，然后操作方块
	// 操作方块的时候用
	void setBlock(int worldPos[], Block::blockType type);//xyz是block世界坐标，放置方块
	Block::blockType getBlockType(int x, int y, int z);//xyz是block世界坐标，得到该位置block类型
	int getBlockHeight(int x, int y);//得到最贴近地表的空气块纵坐标
	// 预留接口，还没想好名字
	// 通过摄像机和方块的交线判断删除方块；没参数
	// 通过摄像机和方块的交线判断添加方块；没参数
	// 或者可以合并到一起

	const static float vertices[];
	const static size_t vsize;
};

#endif 