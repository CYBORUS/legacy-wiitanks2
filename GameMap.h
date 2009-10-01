#ifndef _GAMEMAP_H
#define	_GAMEMAP_H

#include <cstdlib>
#include <fstream>
#include <string>
#include "SDL_Tools.h"
#include "GameEngine.h"
#include "VideoLayer.h"
using namespace std;

#define TILE_SIZE 25



struct Tile
{
    int type;
    bool blockTank;
    bool blockBullet;
};

class GameMap
{
    public:
        GameMap(const char* inFile);
        virtual ~GameMap();

        int getWidth();
        int getHeight();
        Tile* getTile(int inX, int inY);
        Surface getImage(int inIndex);
        Surface getSurface();

    private:
        int mWidth;
        int mHeight;
        int mNumImages;
        Surface* mImages;
        Surface mSurface;

        Tile** mTiles;
};

#endif
