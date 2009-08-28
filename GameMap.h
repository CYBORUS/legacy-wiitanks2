#ifndef _GAMEMAP_H
#define	_GAMEMAP_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <SDL.h>
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
        SDL_Surface* getImage(int inIndex);
        SDL_Surface* getSurface();

    private:
        int mWidth;
        int mHeight;
        int mNumImages;
        SDL_Surface** mImages;
        SDL_Surface* mSurface;

        Tile** mTiles;
};

#endif
