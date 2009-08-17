#ifndef _GAMEMAP_H
#define	_GAMEMAP_H

#include <fstream>
using namespace std;

struct Tile
{
    unsigned int type;
    bool barrier;
};

class GameMap
{
    public:
        GameMap(unsigned int inWidth, unsigned int inHeight, ifstream inMap);
        virtual ~GameMap();

        unsigned int getWidth();
        unsigned int getHeight();
        Tile* getTile(unsigned int inX, unsigned int inY);

    private:
        unsigned int mWidth;
        unsigned int mHeight;
        Tile** mTiles;
};

#endif
