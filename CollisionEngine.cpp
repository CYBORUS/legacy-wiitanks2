#include "CollisionEngine.h"

ProximityMap* CollisionEngine::mProxMap = NULL;


void CollisionEngine::setup(GameMap* inMap)
{
    mProxMap = new ProximityMap(inMap, PROXIMITY_SIZE);
}

bool CollisionEngine::tankMove(VideoLayer* inLayer, int inIntendedX, int inIntendedY)
{

    return false;
}

bool CollisionEngine::bulletMove(Coor* currentPos, Coor* currentVector, VideoLayer* inLayer)
{
    Coor destPos;

    Coor startTile;
    Coor endTile;

    //assume you were able to move the entire direction
    destPos.x = currentPos->x + currentVector->x;
    destPos.y = currentPos->y + currentVector->y;

    int topLeftBefore = currentPos->x / TILE_SIZE;
    int topRightBefore = (currentPos->x + inLayer->surface->w) / TILE_SIZE;
    int bottomLeftBefore = (currentPos->y + inLayer->surface->h) / TILE_SIZE;
    //int bottomRightBefore = (currentPos->


    if ((currentPos->x / TILE_SIZE) != (destPos.x / TILE_SIZE) || startTile.y != endTile.y)
    {
        //we crossed a tile somewhere, so check for walls, etc.
    }



    return false;
}
