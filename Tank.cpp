#include "Tank.h"

#include <iostream>
using namespace std;

/*
*   Tank constructor
*
*   int inBodyGraphic: A number representing which picture in a preloaded array
*       is to be used for this tanks body.
*
*   int inTurretGraphic: A number representing which picture in a preloaded
*       array is to be used for this tanks turret.
*
*   VideoLayer* inLayer: A pointer to the VideoLayer holding this tanks information,
*       this is used to allow each tank to control their own position and movements.
*/
Tank::Tank(int inBodyGraphic, int inTurretGraphic, VideoLayer* inLayer)
{
    mTankBody.graphic = inBodyGraphic;
    mTankBody.angle = 0;

    mTurret.graphic = inTurretGraphic;
    mTurret.angle = 0;

    mMoveDirection = new int[2];

    mMoveDirection[0] = 0;
    mMoveDirection[1] = 0;

    mCurrentTank = NULL;

    mLayer = inLayer;
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

/*
*   moveTank()
*
*   Tells the tank to move in a certain direction.
*
*   int inDirection: An angle representing the direction
*       we want the tank to move in.
*/
void Tank::moveTankX(int inDirection)
{
    mMoveDirection[0] = inDirection;

}

void Tank::moveTankY(int inDirection)
{
    mMoveDirection[1] = inDirection;
}

void Tank::updateTank()
{

    if (mMoveDirection[0] != 0 || mMoveDirection[1] != 0)
    {
        int moveAngle = (int) (atan2((double)mMoveDirection[0], (double)mMoveDirection[1]) + 360) % 360;

        //we will need an x and y value eventually to move the tank
        int x = 0;
        int y = 0;

        //if our front is facing where we want to move, just move
        if (moveAngle != mTankBody.angle)
        {
            int backAngle = (mTankBody.angle + 180) % 360;

            //if our back is facing where we want to move, just move
            if (moveAngle != backAngle)
            {

                //calculate how far the tank would have to turn
                //if it moved forward and if it moved backwards
                int difFront = mTankBody.angle - moveAngle;
                int difBack = backAngle - moveAngle;

                //speed is all important :)
                int absDifFront = abs(difFront);
                int absDifBack = abs(difBack);


                if (absDifFront <= absDifBack)
                {
                    x = (int) sin(mTankBody.angle * PI / 180);
                    y = (int) cos(mTankBody.angle * PI / 180);

                    mLayer->location.x += x;
                    mLayer->location.y += y;

                    turnTank(difFront / absDifFront);

                }
                else
                {
                    x = (int) cos(backAngle * PI / 180);
                    y = (int) sin(backAngle * PI / 180);

                    mLayer->location.x += x;
                    mLayer->location.y += y;

                    turnTank(difBack / absDifBack);
                }
            }
            else
            {
                x = (int) sin(backAngle * PI / 180);
                y = (int) cos(backAngle * PI / 180);

                mLayer->location.x += x;
                mLayer->location.y += y;
            }
        }
        else
        {
            x = (int) sin(mTankBody.angle * PI / 180);
            y = (int) cos(mTankBody.angle * PI / 180);

            mLayer->location.x += x;
            mLayer->location.y += y;
        }
        cerr << "x = " << x << " y = " << y << endl;

    }


}

SDL_Surface* Tank::getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics)
{
    SDL_FreeSurface(mCurrentTank);

    SDL_Surface* tempTurretSurface;
    SDL_Rect location;

    mCurrentTank = SDL_DisplayFormatAlpha(inTankGraphics[mTankBody.graphic].getSurface(mTankBody.angle));

    tempTurretSurface = inTurretGraphics[mTurret.graphic].getSurface(mTurret.angle);
    //tempSurface = SDL_DisplayFormat(inTankGraphics->getSurface(mTankBody.angle));

    location.x = mCurrentTank->w / 2 - tempTurretSurface->w / 2;
    location.y = mCurrentTank->h / 2 - tempTurretSurface->h / 2;

    SDL_BlitSurface(tempTurretSurface, NULL, mCurrentTank, &location);

    return mCurrentTank;
}
