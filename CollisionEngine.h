#ifndef _COLLISIONENGINE_H
#define _COLLISIONENGINE_H

#include <cstdlib>
using namespace std;

#include "ProximityMap.h"
#include "GameMap.h"
#include "VideoLayer.h"
#include "Bullet.h"

#define PROXIMITY_SIZE 2

struct Coor;

class CollisionEngine
{
    public:
        static void setup(GameMap* inMap);

        static bool tankMove(VideoLayer* inLayer, int inIntendedX, int inIntendedY);
        static bool bulletMove(Coor* currentPos, Coor* currentVector, VideoLayer* inLayer);

    private:
        static ProximityMap* mProxMap;
};

#endif
