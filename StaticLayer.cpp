#include "StaticLayer.h"

StaticLayer::StaticLayer() : VideoLayer()
{
    location = new SDL_Rect();
    location->x = 0;
    location->y = 0;
}

StaticLayer::~StaticLayer()
{
}

void StaticLayer::setLocation(int inX, int inY)
{
    location->x = inX;
    location->y = inY;
}
