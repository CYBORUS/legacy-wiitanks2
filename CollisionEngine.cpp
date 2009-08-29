#include "CollisionEngine.h"

ProximityMap* CollisionEngine::mProxMap = NULL;
GameMap* CollisionEngine::mMap = NULL;


void CollisionEngine::setup(GameMap* inMap)
{
    mProxMap = new ProximityMap(inMap, PROXIMITY_SIZE);
    mMap = inMap;
}

bool CollisionEngine::tankMove(VideoLayer* inLayer, int inIntendedX, int inIntendedY)
{
    //Find where each corner would be if we moved the tank
//    Tile* topLeft = getTopLeft(inIntendedX, inIntendedY, inLayer);
//    Tile* topRight = getTopRight(inIntendedX, inIntendedY, inLayer);
//    Tile* bottomLeft = getBottomLeft(inIntendedX, inIntendedY, inLayer);
//    Tile* bottomRight = getBottomRight(inIntendedX, inIntendedY, inLayer);

    //int tileX = inIntendedX / TILE_SIZE;
    //int tileY = inIntendedY / TILE_SIZE;

    //how far into the tile did we go?
    //int diffX = inIntendedX % TILE_SIZE;
    //int diffY = inIntendedY % TILE_SIZE;

    int newX = inIntendedX + inLayer->location.x;
    int newY = inIntendedY + inLayer->location.y;

    //bool tankMoved = true;

    cerr << "curX: " << inLayer->location.x << " curY: " << inLayer->location.y << endl;
    cerr << "inX: " << inIntendedX << " inY: " << inIntendedY << endl;
    cerr << "newX: " << newX << " newY: " << newY << endl;

    //Tile* tile = mMap->getTile(tileX, tileY);

//    while (tankMoved)
//    {
//        tankMoved = false;

        if (getTopLeft(newX, newY, inLayer)->blockTank)
        {
            //tankMoved = true;

            //if just moving the x coord on this corner causes it to block
            if (getTopLeft(newX, inLayer->location.y, inLayer)->blockTank)
            {
                newX += 25 - (newX % TILE_SIZE);
            }

            //if just moving the y coord on this corner causes it to block
            if (getTopLeft(inLayer->location.x, newY, inLayer)->blockTank)
            {
                cerr << "shifting y top left" << endl;
                newY += 25 - (newY % TILE_SIZE);
            }

        }

        if (getTopRight(newX, newY, inLayer)->blockTank)
        {
            //tankMoved = true;

            //if just moving the x coord on this corner causes it to block
            if (getTopRight(newX, inLayer->location.y, inLayer)->blockTank)
            {
                newX -= ((newX + inLayer->surface->w) % TILE_SIZE);
            }

            //if just moving the y coord on this corner causes it to block
            if (getTopRight(inLayer->location.x, newY, inLayer)->blockTank)
            {
                cerr << "shifting y top right" << endl;
                newY += 25 - (newY % TILE_SIZE);
            }
        }

        if (getBottomLeft(newX, newY, inLayer)->blockTank)
        {
            //tankMoved = true;

            //if just moving the x coord on this corner causes it to block
            if (getBottomLeft(newX, inLayer->location.y, inLayer)->blockTank)
            {
                newX += 25 - (newX % TILE_SIZE);
            }

            //if just moving the y coord on this corner causes it to block
            if (getBottomLeft(inLayer->location.x, newY, inLayer)->blockTank)
            {
                cerr << "shifting y bottom left" << endl;
                newY -= ((newY + inLayer->location.h) % TILE_SIZE);
            }
        }

        if (getBottomRight(newX, newY, inLayer)->blockTank)
        {
            //tankMoved = true;

            //if just moving the x coord on this corner causes it to block
            if (getBottomRight(newX, inLayer->location.y, inLayer)->blockTank)
            {
                newX -= ((newX + inLayer->location.w) % TILE_SIZE);
            }

            //if just moving the y coord on this corner causes it to block
            if (getBottomRight(inLayer->location.x, newY, inLayer)->blockTank)
            {
                cerr << "shifting y bottom right" << endl;
                newY -= ((newY + inLayer->location.h) % TILE_SIZE);
            }
        }
    //}

    cerr << "newX after: " << newX << " newY after: " << newY << endl;

    inLayer->setLocation(newX, newY);
    return false;
}

bool CollisionEngine::bulletMove(Coor* currentPos, Coor* currentVector, VideoLayer* inLayer)
{
//    Coor destPos;
//
//    Coor startTile;
//    Coor endTile;
//
//    //assume you were able to move the entire direction
//    destPos.x = currentPos->x + currentVector->x;
//    destPos.y = currentPos->y + currentVector->y;
//
//    int topLeftBefore = currentPos->x / TILE_SIZE;
//    int topRightBefore = (currentPos->x + inLayer->surface->w) / TILE_SIZE;
//    int bottomLeftBefore = (currentPos->y + inLayer->surface->h) / TILE_SIZE;
//    //int bottomRightBefore = (currentPos->
//
//
//    if ((currentPos->x / TILE_SIZE) != (destPos.x / TILE_SIZE) || startTile.y != endTile.y)
//    {
//        //we crossed a tile somewhere, so check for walls, etc.
//    }




    return false;
}

inline Tile* CollisionEngine::getTopLeft(int inX, int inY, VideoLayer* inLayer)
{
    return mMap->getTile(inX / TILE_SIZE, inY / TILE_SIZE);
}

inline Tile* CollisionEngine::getTopRight(int inX, int inY, VideoLayer* inLayer)
{
    return mMap->getTile((inX + inLayer->surface->w - 1) / TILE_SIZE, inY / TILE_SIZE);
}

inline Tile* CollisionEngine::getBottomLeft(int inX, int inY, VideoLayer* inLayer)
{
    return mMap->getTile(inX / TILE_SIZE, (inY + inLayer->surface->h - 1) / TILE_SIZE);
}

inline Tile* CollisionEngine::getBottomRight(int inX, int inY, VideoLayer* inLayer)
{
    return mMap->getTile((inX + inLayer->surface->w - 1) / TILE_SIZE, (inY + inLayer->surface->h - 1) / TILE_SIZE);
}
