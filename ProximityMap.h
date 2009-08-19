#ifndef _PROXIMITYMAP_H
#define	_PROXIMITYMAP_H

#include "GameMap.h"

struct Proximity
{
    int numEntities;
    // pointer to linked list
};

class ProximityMap
{
    public:
        ProximityMap(GameMap* inMap, int inProximitySize);
        virtual ~ProximityMap();
    private:
        int mProximitySize;
        int mGMapWidth;
        int mGMapHeight;
        int mPMapWidth;
        int mPMapHeight;
};

#endif
