#include <cstdlib>
#include "GameMap.h"

GameMap::GameMap(unsigned int inWidth, unsigned int inHeight)
{
    mWidth = inWidth;
    mHeight = inHeight;

    mTiles = new Tile*[mWidth];
    for (unsigned int i = 0; i < mWidth; i++) mTiles[i] = new Tile[mHeight];
}

GameMap::~GameMap()
{
}

unsigned int GameMap::getWidth()
{
    return mWidth;
}

unsigned int GameMap::getHeight()
{
    return mHeight;
}

Tile* GameMap::getTile(unsigned int inX, unsigned int inY)
{
    if (inX >= mWidth || inY >= mHeight) return NULL;
    return &mTiles[inX][inY];
}
