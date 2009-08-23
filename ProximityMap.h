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
        ProximityMap(int inWidth, int inHeight, int inProximitySize);
        ProximityMap(GameMap* inMap, int inProximitySize);
        virtual ~ProximityMap();

        void insertEntity(int inGMapX, int inGMapY);

    private:
        void build();

        bool mValid;
        Proximity** mPMap;
        int mProximitySize;
        int mGMapWidth;
        int mGMapHeight;
        int mPMapWidth;
        int mPMapHeight;
};

#endif
