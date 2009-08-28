#ifndef _PROXIMITYMAP_H
#define	_PROXIMITYMAP_H

#include "GameMap.h"
#include "Entity.h"

struct EntityLink
{
    Entity* entity;
    EntityLink* next;
};

struct Proximity
{
    int numEntities;
    EntityLink* list;
};

class ProximityMap
{
    public:
        ProximityMap(int inWidth, int inHeight, int inProximitySize);
        ProximityMap(GameMap* inMap, int inProximitySize);
        virtual ~ProximityMap();

        void insertEntity(Entity* inEntity, int inGMapX, int inGMapY);

    private:
        void build();
        void putEntity(Entity* inEntity, int inPMapX, int inPMapY);

        bool mValid;
        Proximity** mPMap;
        int mProximitySize;
        int mGMapWidth;
        int mGMapHeight;
        int mPMapWidth;
        int mPMapHeight;
};

#endif
