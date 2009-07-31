#include "Bullet.h";

#include <iostream>
using namespace std;

Bullet::Bullet(double inVX, double inVY, double inPX, double inPY, double inMagnitude)
{
    double ratio = inMagnitude / sqrt(pow(inVX, 2) + pow(inVY, 2));
    mVector.x = inVX * ratio;
    mVector.y = inVY * ratio;

    mPos.x = inPX;
    mPos.y = inPY;

    mBullet = new VideoLayer();
    mBullet->priority = PRIORITY_DEFAULT;
    mBullet->surface = VideoLayer::getImage("images/bullet.png");
}

VideoLayer* Bullet::getLayer()
{
    return mBullet;
}

void Bullet::onUpdate()
{
    mPos.x += mVector.x;
    mPos.y += mVector.y;

    mBullet->setLocation((int)mPos.x, (int)mPos.y);
}
