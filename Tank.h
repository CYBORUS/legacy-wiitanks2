#ifndef _TANK_H
#define _TANK_H

#include <SDL.h>
#include <SDL_image.h>
#include "RotatedGraphic.h"


struct Direction
{
    int graphic;
    int angle;
};

class Tank
{
    public:
        Tank(int inBodyGraphic, int inTurretGraphic);

        void setBody(int inAngle);
        void setTurret(int inAngle);

        void turnTank(int inOffset);

        SDL_Surface* getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics);


    private:
        Direction mTankBody;
        Direction mTurret;
        SDL_Surface* mCurrentTank;

};

#endif
