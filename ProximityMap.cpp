#include "ProximityMap.h"

ProximityMap::ProximityMap(GameMap* inMap, int inProximitySize)
{
    mProximitySize = inProximitySize;
    mGMapWidth = inMap->getWidth();
    mGMapHeight = inMap->getHeight();

    mPMapWidth = mGMapWidth / (mProximitySize - 1);
}

ProximityMap::~ProximityMap()
{
}
