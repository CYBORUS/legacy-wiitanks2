#ifndef _GAMEMAP_H
#define	_GAMEMAP_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <SDL.h>
#include "VideoLayer.h"
using namespace std;

#define TILE_SIZE 25

struct Tile
{
    unsigned int type;
    bool barrier;
};

class GameMap
{
    public:
        GameMap(unsigned int inWidth, unsigned int inHeight);
        GameMap(const char* inFile);
        virtual ~GameMap();

        unsigned int getWidth();
        unsigned int getHeight();
        Tile* getTile(unsigned int inX, unsigned int inY);

    private:
        unsigned int mWidth;
        unsigned int mHeight;
        unsigned int mNumImages;
        SDL_Surface** mImages;

        Tile** mTiles;
};

#endif
