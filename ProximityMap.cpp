#include "ProximityMap.h"

ProximityMap::ProximityMap(int inWidth, int inHeight, int inProximitySize)
{
    // get passed data
    mProximitySize = inProximitySize;
    mGMapWidth = inWidth;
    mGMapHeight = inHeight;

    build();
}

ProximityMap::ProximityMap(GameMap* inMap, int inProximitySize)
{
    // requires a valid GameMap object
    if (inMap == NULL) return;

    // get passed data
    mProximitySize = inProximitySize;
    mGMapWidth = inMap->getWidth();
    mGMapHeight = inMap->getHeight();

    build();
}

ProximityMap::~ProximityMap()
{
    if (!mValid) return;

    for (int i = 0; i < mPMapHeight; i++)
    {
        delete [] mPMap[i];
    }

    delete [] mPMap;
}

/**
 * This function is here simply to prevent redundant code in the various
 * constructors.
 */
void ProximityMap::build()
{
    // assume an invalid map
    mValid = false;

    // calculate the necessary number of proximities
    mPMapWidth = (mGMapWidth - 2) / (mProximitySize - 1) + 1;
    mPMapHeight = (mGMapHeight - 2) / (mProximitySize - 1) + 1;

    // do not attempt to create a negative or zero sized map
    if (mPMapWidth < 1 || mPMapHeight < 1) return;

    // if we make it this far, we know we have a valid map
    mValid = true;

    mPMap = new Proximity*[mPMapHeight];
    for (int i = 0; i < mPMapHeight; i++)
    {
        mPMap[i] = new Proximity[mPMapWidth];
        for (int j = 0; j < mPMapWidth; j++)
        {
            mPMap[i][j].numEntities = 0;
        }
    }
}

void ProximityMap::insertEntity(Entity* inEntity, int inGMapX, int inGMapY)
{
    if (!mValid) return;

    int highX = inGMapX / (mProximitySize - 1);
    int lowX = (inGMapX - 1) / (mProximitySize - 1);

    int highY = inGMapY / (mProximitySize - 1);
    int lowY = (inGMapY - 1) / (mProximitySize - 1);

    putEntity(inEntity, lowX, lowY);
    if (lowX < highX)
    {
        putEntity(inEntity, highX, lowY);
        if (lowY < highY)
        {
            putEntity(inEntity, lowX, highY);
            putEntity(inEntity, highX, highY);
        }
    }
    else if (lowY < highY)
    {
        putEntity(inEntity, lowX, highY);
    }
}

void ProximityMap::putEntity(Entity* inEntity, int inPMapX, int inPMapY)
{
    EntityLink* el = new EntityLink;
    el->entity = inEntity;
    el->next = mPMap[inPMapX][inPMapY].list;
    mPMap[inPMapX][inPMapY].numEntities++;
    mPMap[inPMapX][inPMapY].list = el;
}
