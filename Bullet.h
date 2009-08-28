#ifndef _BULLET_H
#define _BULLET_H

#include <cmath>
#include "VideoLayer.h"
#include "CollisionEngine.h"
#include "Entity.h"
using namespace std;

struct Coor
{
    double x;
    double y;
};

class Bullet : public Entity
{
    public:
        Bullet(double inVX, double inVY, double inPX, double inPY, double inMagnitude);
        //virtual ~Bullet();

         void onUpdate();
         VideoLayer* getLayer();




    private:
        Coor mVector;
        Coor mPos;

        VideoLayer* mBullet;
};

#endif
