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
        double moveAmount = 10.0;
        int moveAngle = (int) ((atan2((double)mMoveDirection[1], (double)mMoveDirection[0]) * 180 / PI) + 360) % 360;

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
                int difFront = moveAngle - mTankBody.angle;
                int difBack = backAngle - moveAngle;

                //speed is all important :)
                int absDifFront = abs(difFront);
                int absDifBack = abs(difBack);

                int turn = 0;


                if (absDifFront <= absDifBack)
                {
                    x = (int) (cos((double)mTankBody.angle * PI / 180.0) * moveAmount);
                    y = (int) (sin((double)mTankBody.angle * PI / 180.0) * moveAmount) * -1;

                     cerr << "moving/turning front " << x << ", " << y  << endl;
                    mLayer->location.x += x;
                    mLayer->location.y += y;

                    turn = difFront / absDifBack * TURN_RATE;

                    if (turn > (mTankBody.angle - moveAngle))
                    {

                    }

                    if ((x > 0 && y < 0) || (x < 0 && y > 0) ||
                        (y < 0 && mTankBody.angle < 90))
                    {
                        turnTank(abs(difFront / absDifFront * TURN_RATE));
                    }
                    else
                    {
                        if (difFront > 0)
                        {
                            difFront *= -1;
                        }
                        turnTank(difFront / absDifFront * TURN_RATE);
                    }
                }
                else
                {
                    x = (int) (cos((double)backAngle * PI / 180.0) * moveAmount);
                    y = (int) (sin((double)backAngle * PI / 180.0) * moveAmount) * -1;
                    cerr << "moving/turning back " << x << ", " << y << endl;

                    mLayer->location.x += x;
                    mLayer->location.y += y;

                    if ((x > 0 && y < 0) || (x < 0 && y > 0) ||
                        (y < 0 && backAngle < 90))
                    {
                        turnTank(abs(difBack / absDifBack * TURN_RATE));
                    }
                    else
                    {
                        if (difBack > 0)
                        {
                            difBack *= -1;
                        }
                        turnTank(difBack / absDifBack * TURN_RATE);
                    }

                }
            }
            else
            {
                x = (int) (cos((double)backAngle * PI / 180.0) * moveAmount);
                y = (int) (sin((double)backAngle * PI / 180.0) * moveAmount) * -1;
                cerr << "moving back " << x << ", " << y  << endl;

                mLayer->location.x += x;
                mLayer->location.y += y;
            }
        }
        else
        {
            x = (int) (cos((double)mTankBody.angle * PI / 180.0) * moveAmount);
            y = (int) (sin((double)mTankBody.angle * PI / 180.0) * moveAmount) * -1;
            cerr << "moving front " << x << ", " << y  << endl;

            mLayer->location.x += x;
            mLayer->location.y += y;
        }
        //cerr << "x = " << x << " y = " << y << endl;

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
