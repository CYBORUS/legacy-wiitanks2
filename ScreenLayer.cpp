#include <iostream>
#include "ScreenLayer.h"
using namespace std;

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
        SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if (surface == NULL) return false;

    cerr << "hw available? " << (SDL_GetVideoInfo()->hw_available ? "yes" : "no") << endl;
    cerr << "flag check: " << surface->flags << endl;
    //cerr << "flag check: " << (surface->flags & SDL_HWSURFACE) << endl;
    cerr << "hardware surface? " << ((surface->flags & SDL_HWSURFACE) > 0 ? "yes" : "no") << endl;

    return true;
}
