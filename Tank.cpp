#include "Tank.h"



Tank::Tank(int inBodyGraphic, int inTurretGraphic)
{
    mTankBody.graphic = inBodyGraphic;
    mTankBody.angle = 0;

    mTurret.graphic = inTurretGraphic;
    mTurret.angle = 0;
}

void Tank::setBody(int inAngle)
{
    mTankBody.angle = inAngle;
}


void Tank::setTurret(int inAngle)
{
    mTurret.angle = inAngle;
}

SDL_Surface* Tank::getTank(RotatedGraphic* inGraphics)
{
    SDL_Surface* tempSurface;

    tempSurface = SDL_DisplayFormat(inGraphics[mTankBody.graphic].getSurface(mTankBody.angle));

    SDL_BlitSurface(inGraphics[mTurret.graphic].getSurface(mTurret.angle), NULL, tempSurface, NULL);

    return tempSurface;
}
