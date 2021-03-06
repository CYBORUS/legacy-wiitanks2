#ifndef _TANK_H
#define _TANK_H

#include "SDL_Tools.h"
#include <SDL_image.h>
#include <cmath>
#include "RotatedGraphic.h"
#include "VideoLayer.h"
#include "GameMap.h"
#include "CollisionEngine.h"
#include "Entity.h"

#define PI 3.14159265
#define TURN_RATE 10

struct Direction
{
    int graphic;
    int angle;
};

class Tank : public Entity
{
    public:
        Tank(int inBodyGraphic, int inTurretGraphic, VideoLayer* inLayer);

        void setBody(int inAngle);
        void setTurret(int inAngle);

        void turnTank(int inOffset);
        void moveTankX(int inDirection);
        void moveTankY(int inDirection);

        void updateTank(GameMap* inMap);

        Surface getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics);


    private:
        Direction mTankBody;
        Direction mTurret;
        Surface mCurrentTank;
        VideoLayer* mLayer;

        int* mMoveDirection;
        double mTankSpeed;

};

#endif
