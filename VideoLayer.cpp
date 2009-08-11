#include <iostream>
#include "VideoLayer.h"
using namespace std;


VideoLayer::VideoLayer()
{
    //std::cerr << "new layer\n";
    priority = 0;
    next = NULL;
    surface = NULL;
    clip = NULL;
    location.x = 0;
    location.y = 0;
}

VideoLayer::~VideoLayer()
{
}

SDL_Surface* VideoLayer::getImage(const char* inFile)
{
    SDL_Surface* t = NULL;
    SDL_Surface* u = NULL;
    SDL_Surface* outSurface = NULL;

    if((t = IMG_Load(inFile)) == NULL)
    {
        cerr << "Failed to load " << inFile << endl;
        return NULL;
    }

    Uint32 rmask, gmask, bmask, amask;

    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    }
    else
    {
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    }

    u = SDL_DisplayFormatAlpha(t);
    SDL_FreeSurface(t);
    outSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, t->w, t->h,
        32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(u, NULL, outSurface, NULL);
    SDL_FreeSurface(u);

    return outSurface;
}

void VideoLayer::setLocation(int inX, int inY)
{
    location.x = inX;
    location.y = inY;
}

//void VideoLayer::overlay(SDL_Surface* inTarget, SDL_Surface* inSurface)
//{
//    if (inTarget == NULL || inSurface == NULL) return;
//    SDL_BlitSurface(inSurface, NULL, inTarget, NULL);
//}
//
//void VideoLayer::overlay(SDL_Surface* inTarget, SDL_Surface* inSurface,
//    SDL_Rect* inLocation)
//{
//    if (inTarget == NULL || inSurface == NULL) return;
//    SDL_BlitSurface(inSurface, NULL, inTarget, inLocation);
//}
//
//void VideoLayer::overlay(SDL_Surface* inTarget, SDL_Surface* inSurface,
//    int inX, int inY)
//{
//    if (inTarget == NULL || inSurface == NULL) return;
//
//    SDL_Rect location;
//
//    location.x = inX;
//    location.y = inY;
//
//    SDL_BlitSurface(inSurface, NULL, inTarget, &location);
//}
