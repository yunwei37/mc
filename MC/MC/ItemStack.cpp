#include "ItemStack.h"

int ItemStack::add(int type, int amount)
{
    if (numInStack + amount > MAXSIZE_STACK)
    {
        return -1;
    }
    else 
    {
        numInStack += amount;
        bag[type] += amount;
        return 0;
    }
}

int ItemStack::takeout(int type)
{
    if (bag[type] == 0)
    {
        return -1;
    }
    else
    {
        bag[type]--;
        return 0;
    }
}

int ItemStack::remove(int type)
{
    if (numInStack == 0)
    {
        return -1;
    }
    else
    {
        numInStack--;
        return 0;
    }
}

int ItemStack::getNumInStack() const
{
    return numInStack;
}

