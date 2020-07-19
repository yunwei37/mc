#pragma once
#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include <string>

#define MAXSIZE_STACK 50
#define MAXTYPE 25
#define EMPTY 0
#define GRASS 1
#define SAND 2
#define STONE 3
#define BRICK 4
#define WOOD 5
#define CEMENT 6
#define DIRT 7
#define PLANK 8
#define SNOW 9
#define GLASS 10
#define COBBLE 11
#define LIGHT_STONE 12
#define DARK_STONE 13
#define CHEST 14
#define LEAVES 15
#define CLOUD 16
#define TALL_GRASS 17
#define YELLOW_FLOWER 18
#define RED_FLOWER 19
#define PURPLE_FLOWER 20
#define SUN_FLOWER 21
#define WHITE_FLOWER 22
#define BLUE_FLOWER 23

struct ItemStack
{
public:
    int bag[MAXTYPE];
    int add(int type, int amount);
    int takeout(int type);
    int remove(int type);
    int getNumInStack() const;

private:
    int numInStack;
};

#endif // 