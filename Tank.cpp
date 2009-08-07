#include "Tank.h"

#include <iostream>
using namespace std;

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

void Tank::turnTank(int inOffset)
{
    mTankBody.angle += inOffset;

    while(mTankBody.angle < 0)
    {
        mTankBody.angle += 360;
    }

    mTankBody.angle %= 360;

}

SDL_Surface* Tank::getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics)
{
    SDL_Surface* tempTankSurface;
    SDL_Surface* tempTurretSurface;
    SDL_Rect location;

    tempTankSurface = SDL_DisplayFormatAlpha(inTankGraphics[mTankBody.graphic].getSurface(mTankBody.angle));

    tempTurretSurface = inTurretGraphics[mTurret.graphic].getSurface(mTurret.angle);
    //tempSurface = SDL_DisplayFormat(inTankGraphics->getSurface(mTankBody.angle));

    location.x = tempTankSurface->w / 2 - tempTurretSurface->w / 2;
    location.y = tempTankSurface->h / 2 - tempTurretSurface->h / 2;

    SDL_BlitSurface(tempTurretSurface, NULL, tempTankSurface, &location);

    return tempTankSurface;
}
