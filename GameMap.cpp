#include "GameMap.h"

GameMap::GameMap(unsigned int inWidth, unsigned int inHeight)
{
    mWidth = inWidth;
    mHeight = inHeight;

    mTiles = new Tile*[mWidth];
    for (unsigned int i = 0; i < mWidth; i++) mTiles[i] = new Tile[mHeight];
}

GameMap::GameMap(const char* inFile)
{
    ifstream file;
    file.open(inFile);

    file >> mWidth >> mHeight >> mNumImages;

    mTiles = new Tile*[mWidth];
    for (unsigned int i = 0; i < mWidth; i++) mTiles[i] = new Tile[mHeight];
    mImages = new SDL_Surface*[mNumImages];

    for (unsigned int i = 0; i < mNumImages; i++)
    {
        int index;
        string imageFile;
        file >> index >> imageFile;
        mImages[index] = VideoLayer::getImage(imageFile.c_str());
    }

    for (unsigned int i = 0; i < mHeight; i++)
    {
        for (unsigned int j = 0; j < mWidth; j++)
        {
            file >> mTiles[j][i].type;
            mTiles[j][i].barrier = false;
        }
    }

    file.close();
}

GameMap::~GameMap()
{
    if (mWidth == 0 || mHeight == 0) return;
    for (unsigned int i = 0; i < mWidth; i++) delete [] mTiles[i];
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
