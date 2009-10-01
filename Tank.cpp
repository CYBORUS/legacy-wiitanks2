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

    mTankSpeed = 5.0;
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

void Tank::updateTank(GameMap* inMap)
{
    if (mMoveDirection[0] == 0 && mMoveDirection[1] == 0) return;

    int moveAngle = (int) (atan2((double)mMoveDirection[1], (double)mMoveDirection[0]) * 180 / PI);

    //we will need an x and y value eventually to move the tank
    int intendedX = 0;
    int intendedY = 0;

    int backAngle = (mTankBody.angle + 180) % 360;

    int difFront;
    int difBack;
    int absDifFront;
    int absDifBack;

    int tempFront = mTankBody.angle;
    int tempBack = backAngle;


    //we temporarilly need these angles in the same format as atan2 returns
    if (mTankBody.angle > 180)
    {
        tempFront -= 360;
    }

    if (backAngle > 180)
    {
        tempBack -= 360;
    }

    int absFront = abs(tempFront);
    int absBack = abs(tempBack);
    int absMoveAngle = abs(moveAngle);

    //In order to determine the difference between the front and back of the tank
    //and the angle we want to be moving, we have to deal with the problem of
    //crossing the 0 point on the unit circle.  In other words,
    //going from 1 degree to 359 degrees is NOT a difference of 358 degrees,
    //it's a difference of 2 degrees.  The following if statements solve
    //that problem for both the front and back ends of the tank.

    //If both angles are in the same half of the circle (top or bottom)
    //the math is the same for all cases
    if ((tempFront > 0 && moveAngle > 0) ||
        (tempFront < 0 && moveAngle < 0))
    {
        difFront = (moveAngle - tempFront);
    }
    else if ((difFront = absFront + absMoveAngle) <= 180)
    {
        //We need the side of the angle that is less than 180 degrees

        //The assignment in this if statement takes care of difFront here
        //We do need to know which way it should turn, though
        if (moveAngle < tempFront)
        {
            difFront *= -1;
        }

    }
    else
    {
        //We need a different angle for this case

        difFront = (180 - absMoveAngle) + (180 - absFront);

        //The assignment in the outer if statement takes care of difFront here
        //We do need to know which way it should turn, though
        if (moveAngle > tempFront)
        {
            difFront *= -1;
        }
    }
    absDifFront = abs(difFront);

    //If both angles are in the same half of the circle (top or bottom)
    //the math is the same for all cases
    if ((tempBack > 0 && moveAngle > 0) ||
        (tempBack < 0 && moveAngle < 0))
    {
        difBack = (moveAngle - tempBack);
    }
    else if ((difBack = absBack + absMoveAngle) <= 180)
    {
        //We need the side of the angle that is less than 180 degrees

        //The assignment in this if statement takes care of difFront here
        //We do need to know which way it should turn, though
        if (moveAngle < tempBack)
        {
            difBack *= -1;
        }

    }
    else
    {
        //We need a different angle for this case
        difBack = (180 - absMoveAngle) + (180 - absBack);

        //The assignment in the outer if statement takes care of difFront here
        //We do need to know which way it should turn, though
        if (moveAngle > tempBack)
        {
            difBack *= -1;
        }
    }
    absDifBack = abs(difBack);

    //Now we need to set moveAngle to the 360 degree circle
    moveAngle = (moveAngle + 360) % 360;

    //if our front is facing where we want to move, just move
    if (moveAngle != mTankBody.angle)
    {
        //if our back is facing where we want to move, just move
        if (moveAngle != backAngle)
        {
            //ok, we need to turn the tank toward the desired direction
            int turn = 0;

            if (absDifFront <= absDifBack)
            {
                intendedX = (int) (cos((double)mTankBody.angle * PI / 180.0) * mTankSpeed);
                intendedY = (int) (sin((double)mTankBody.angle * PI / 180.0) * mTankSpeed);

                turn = difFront / absDifFront * TURN_RATE;

                //Don't turn past the desired direction
                if (abs(turn) > absDifFront)
                {
                    turn = absDifFront;

                }

                turnTank(turn);

                CollisionEngine::tankMove(mLayer, intendedX, intendedY);
            }
            else
            {
                intendedX = (int) (cos((double)backAngle * PI / 180.0) * mTankSpeed);
                intendedY = (int) (sin((double)backAngle * PI / 180.0) * mTankSpeed);

                turn = difBack / absDifBack * TURN_RATE;

                //Don't turn past the desired direction
                if (abs(turn) > absDifBack)
                {
                    turn = absDifBack;
                }

                turnTank(turn);

                CollisionEngine::tankMove(mLayer, intendedX, intendedY);
            }
        }
        else
        {
            intendedX = (int) (cos((double)backAngle * PI / 180.0) * mTankSpeed);
            intendedY = (int) (sin((double)backAngle * PI / 180.0) * mTankSpeed);

            CollisionEngine::tankMove(mLayer, intendedX, intendedY);
        }
    }
    else
    {
        intendedX = (int) (cos((double)mTankBody.angle * PI / 180.0) * mTankSpeed);
        intendedY = (int) (sin((double)mTankBody.angle * PI / 180.0) * mTankSpeed);

        CollisionEngine::tankMove(mLayer, intendedX, intendedY);
    }

//    int leftX = mLayer->location.x / TILE_SIZE;
//    int rightX = (mLayer->location.x + mLayer->location.w) / TILE_SIZE;
//    int topY = mLayer->location.y / TILE_SIZE;
//    int bottomY = (mLayer->location.y + mLayer->location.h) / TILE_SIZE;
//
//    if (inMap->getTile(rightX, topY)->blockTank)
//    {
//        if (mMoveDirection[0] > 0)
//        {
//            mLayer->location.x = rightX * TILE_SIZE - mLayer->location.w;
//        }
//
//        if (mMoveDirection[1] < 0)
//        {
//            mLayer->location.y = topY * TILE_SIZE;
//        }
//    }
//
//    if (inMap->getTile(rightX, bottomY)->blockTank)
//    {
//        if (mMoveDirection[0] > 0)
//        {
//            mLayer->location.x = rightX * TILE_SIZE - mLayer->location.w;
//        }
//
//        if (mMoveDirection[1] > 0)
//        {
//            mLayer->location.y = bottomY * TILE_SIZE - mLayer->location.h;
//        }
//    }
//
//    if (inMap->getTile(leftX, topY)->blockTank)
//    {
//        if (mMoveDirection[0] < 0)
//        {
//            mLayer->location.x = (leftX + 1) * TILE_SIZE;
//        }
//
//        if (mMoveDirection[1] < 0)
//        {
//            mLayer->location.y = (topY + 1) * TILE_SIZE;
//        }
//    }
//
//    if (inMap->getTile(leftX, bottomY)->blockTank)
//    {
//        if (mMoveDirection[0] < 0)
//        {
//            mLayer->location.x = (leftX + 1) * TILE_SIZE;
//        }
//
//        if (mMoveDirection[1] > 0)
//        {
//            mLayer->location.y = bottomY * TILE_SIZE - mLayer->location.h;
//        }
//    }
}

Surface Tank::getTank(RotatedGraphic* inTankGraphics, RotatedGraphic* inTurretGraphics)
{
    SDL_FreeSurface(mCurrentTank);

    Surface tempTurretSurface;
    SDL_Rect location;

    mCurrentTank = SDL_DisplayFormatAlpha(inTankGraphics[mTankBody.graphic].getSurface(mTankBody.angle));

    tempTurretSurface = inTurretGraphics[mTurret.graphic].getSurface(mTurret.angle);
    //tempSurface = SDL_DisplayFormat(inTankGraphics->getSurface(mTankBody.angle));

    location.x = mCurrentTank->w / 2 - tempTurretSurface->w / 2;
    location.y = mCurrentTank->h / 2 - tempTurretSurface->h / 2;

    SDL_BlitSurface(tempTurretSurface, NULL, mCurrentTank, &location);

    return mCurrentTank;
}
