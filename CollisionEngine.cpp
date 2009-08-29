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
    int newX = inIntendedX + inLayer->location.x;
    int newY = inIntendedY + inLayer->location.y;


    //We need to make sure that the shifting size of the tank hasn't accidentally put the original
    //corner positions inside a blocked area

    //We don't need to test the top left corner because the changing size of the tank
    //will never change that corners position
    if (getTopRight(inLayer->location.x, inLayer->location.y, inLayer)->blockTank)
    {
        inLayer->location.x -= (inLayer->location.x % TILE_SIZE);
    }

    if (getBottomLeft(inLayer->location.x, inLayer->location.y, inLayer)->blockTank)
    {
        inLayer->location.y -= (inLayer->location.y % TILE_SIZE);
    }

    //The bottom right corner is a special condition, and would need to adjust both x and y
    //coordinates to fix it's position
    if (getBottomRight(inLayer->location.x, inLayer->location.y, inLayer)->blockTank)
    {
        inLayer->location.x -= (inLayer->location.x % TILE_SIZE);
        inLayer->location.y -= (inLayer->location.y % TILE_SIZE);
    }



    //Now we're ready to see if the desired movement of the tank puts it inside a blocked tile
    if (getTopLeft(newX, newY, inLayer)->blockTank)
    {
        //if just moving the x coord on this corner causes it to block
        if (getTopLeft(newX, inLayer->location.y, inLayer)->blockTank)
        {
            newX += 25 - (newX % TILE_SIZE);
        }

        //if just moving the y coord on this corner causes it to block
        if (getTopLeft(inLayer->location.x, newY, inLayer)->blockTank)
        {
            newY += 25 - (newY % TILE_SIZE);
        }

    }

    if (getTopRight(newX, newY, inLayer)->blockTank)
    {
        //if just moving the x coord on this corner causes it to block
        if (getTopRight(newX, inLayer->location.y, inLayer)->blockTank)
        {
            newX -= ((newX + inLayer->surface->w) % TILE_SIZE);
        }

        //if just moving the y coord on this corner causes it to block
        if (getTopRight(inLayer->location.x, newY, inLayer)->blockTank)
        {
            newY += 25 - (newY % TILE_SIZE);
        }
    }

    if (getBottomLeft(newX, newY, inLayer)->blockTank)
    {
        //if just moving the x coord on this corner causes it to block
        if (getBottomLeft(newX, inLayer->location.y, inLayer)->blockTank)
        {
            newX += 25 - (newX % TILE_SIZE);
        }

        //if just moving the y coord on this corner causes it to block
        if (getBottomLeft(inLayer->location.x, newY, inLayer)->blockTank)
        {
            newY -= ((newY + inLayer->location.h) % TILE_SIZE);
        }
    }

    if (getBottomRight(newX, newY, inLayer)->blockTank)
    {
        //if just moving the x coord on this corner causes it to block
        if (getBottomRight(newX, inLayer->location.y, inLayer)->blockTank)
        {
            newX -= ((newX + inLayer->location.w) % TILE_SIZE);
        }

        //if just moving the y coord on this corner causes it to block
        if (getBottomRight(inLayer->location.x, newY, inLayer)->blockTank)
        {
            newY -= ((newY + inLayer->location.h) % TILE_SIZE);
        }
    }

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
