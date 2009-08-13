#ifndef _TANK_H
#define _TANK_H

#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "RotatedGraphic.h"
#include "VideoLayer.h"

#define PI 3.14159265
#define TURN_RATE 10

struct Direction
{
    int graphic;
    int angle;
};

class Tank
{
    public:
        Tank(int inBodyGraphic, int inTurretGraphic, VideoLayer* inLayer);

        void setBody(int inAngle);
        void setTurret(int inAngle);

        void turnTank(int inOffset);
        void moveTankX(int inDirection);
        void moveTankY(int inDirection);

        void updateTank();

        SDL_Surface* getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics);


    private:
        Direction mTankBody;
        Direction mTurret;
        SDL_Surface* mCurrentTank;
        VideoLayer* mLayer;

        int* mMoveDirection;
        double mTankSpeed;

};

#endif
