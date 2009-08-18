#include <iostream>
#include "GameMap.h"
using namespace std;

GameMap::GameMap(const char* inFile)
{
    ifstream file;
    file.open(inFile);

    file >> mWidth >> mHeight >> mNumImages;

    mTiles = new Tile*[mHeight];
    for (int i = 0; i < mHeight; i++) mTiles[i] = new Tile[mWidth];
    mImages = new SDL_Surface*[mNumImages];
    bool* blockTank = new bool[mNumImages];
    bool* blockBullet = new bool[mNumImages];

    for (int i = 0; i < mNumImages; i++)
    {
        int index, bt, bb;
        string imageFile;
        file >> index >> bt >> bb >> imageFile;
        mImages[index] = VideoLayer::getImage(imageFile.c_str());
        blockTank[index] = (bt != 0);
        blockBullet[index] = (bb != 0);

        //if (blockTank[index]) cerr << "blockTank\n";
    }

    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            file >> mTiles[i][j].type;
            mTiles[i][j].blockTank = blockTank[mTiles[i][j].type];
            mTiles[i][j].blockBullet = blockBullet[mTiles[i][j].type];
            //if (mTiles[i][j].blockTank) cerr << "blockTank in tile\n";
        }
    }

    file.close();

    mSurface = GameEngine::newSurface(mWidth * TILE_SIZE, mHeight * TILE_SIZE);

    SDL_Rect d;
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            d.x = i * TILE_SIZE - 4;
            d.y = j * TILE_SIZE - 25;
            SDL_BlitSurface(mImages[mTiles[i][j].type], NULL, mSurface, &d);
        }
    }
}

GameMap::~GameMap()
{
    if (mWidth == 0 || mHeight == 0) return;
    for (int i = 0; i < mHeight; i++) delete [] mTiles[i];
    delete [] mTiles;
}

int GameMap::getWidth()
{
    return mWidth;
}

int GameMap::getHeight()
{
    return mHeight;
}

Tile* GameMap::getTile(int inX, int inY)
{
    if (inX >= mWidth || inY >= mHeight) return NULL;
    return &mTiles[inX][inY];
}

SDL_Surface* GameMap::getSurface()
{
    return mSurface;
}

SDL_Surface* GameMap::getImage(int inIndex)
{
    return mImages[inIndex];
}
