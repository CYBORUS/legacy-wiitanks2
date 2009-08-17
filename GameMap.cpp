#include "GameMap.h"

GameMap::GameMap(unsigned int inWidth, unsigned int inHeight)
{
    mWidth = inWidth;
    mHeight = inHeight;

    mTiles = new Tile*[mHeight];
    for (unsigned int i = 0; i < mHeight; i++) mTiles[i] = new Tile[mWidth];
}

GameMap::GameMap(const char* inFile)
{
    ifstream file;
    file.open(inFile);

    file >> mWidth >> mHeight >> mNumImages;

    mTiles = new Tile*[mHeight];
    for (unsigned int i = 0; i < mHeight; i++) mTiles[i] = new Tile[mWidth];
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
            file >> mTiles[i][j].type;
            mTiles[i][j].barrier = false;
        }
    }

    file.close();

    SDL_Surface* t;
    t = SDL_CreateRGBSurface(SDL_SWSURFACE, mWidth * TILE_SIZE,
        mHeight * TILE_SIZE, 32, GameEngine::mask.red,
        GameEngine::mask.green, GameEngine::mask.blue,
        GameEngine::mask.alpha);
    mSurface = SDL_DisplayFormat(t);
    SDL_FreeSurface(t);

    SDL_Rect d;
    for (unsigned int i = 0; i < mHeight; i++)
    {
        for (unsigned int j = 0; j < mWidth; j++)
        {
            d.x = i * TILE_SIZE - 4;
            d.y = j * TILE_SIZE - 25;
            SDL_BlitSurface(mImages[mTiles[i][j].type], NULL, mSurface, &d);
        }
    }

//    for (int i = 0; i < MAP_SIZE; i++)
//    {
//        mDest.y = i * 25;
//        for (int j = 0; j < MAP_SIZE; j++)
//        {
//            mSrc.x = tileMap[i][j] * 25;
//            mDest.x = j * 25;
//
//            if (SDL_BlitSurface(mTileset->surface, &mSrc, mBackground->surface, &mDest) == -2)
//            {
//                cerr << "blitting failed" << endl;
//                exit(4);
//            }
//        }
//    }


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

SDL_Surface* GameMap::getSurface()
{
    return mSurface;
}
