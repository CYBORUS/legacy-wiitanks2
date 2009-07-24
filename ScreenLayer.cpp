#include "ScreenLayer.h"

ScreenLayer::ScreenLayer() : VideoLayer()
{
    mWidth = 800;
    mHeight = 600;
}

ScreenLayer::~ScreenLayer()
{
}

bool ScreenLayer::setVideoMode()
{
    //SDL_RESIZABLE
    surface = SDL_SetVideoMode(mWidth, mHeight, 0,
        SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (surface == NULL) return false;
    return true;
}
