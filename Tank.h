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

        SDL_Surface* getTank(RotatedGraphic* inGraphics);


    private:
        Direction mTankBody;
        Direction mTurret;

};

#endif
