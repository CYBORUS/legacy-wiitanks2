#include "StaticLayer.h"

StaticLayer::StaticLayer() : VideoLayer()
{
    location = new SDL_Rect();
    location->x = 0;
    location->y = 0;
}

StaticLayer::~StaticLayer()
{
    SDL_FreeSurface(surface);
    surface = NULL;
}

void StaticLayer::setLocation(int inX, int inY)
{
    location->x = inX;
    location->y = inY;
}
