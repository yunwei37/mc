#pragma once
#ifndef PLANTGEN_H
#define PLENTGEN_H
#include"Chunk.h"
//生成地表植物
void makePalmTree(Chunk& chunk, int seed, int x, int y, int z);//generate palm tree
void makeCactus(Chunk& chunk, int seed, int x, int y, int z);//generate cactus

void cactus1(Chunk& chunk, int seed, int x, int y, int z);//generate cactus1
void cactus2(Chunk& chunk, int seed, int x, int y, int z);//generate cactus2

#endif // !PLANTGEN_H
