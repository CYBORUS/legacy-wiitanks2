#include <iostream>
#include "VideoLayer.h"
using namespace std;


VideoLayer::VideoLayer()
{
    //std::cerr << "new layer\n";
    priority = 0;
    next = NULL;
    surface = NULL;
    location = NULL;
    clip = NULL;
}

VideoLayer::~VideoLayer()
{
}

SDL_Surface* VideoLayer::getImage(const char* inFile)
{
    SDL_Surface* t = NULL;
    SDL_Surface* outSurface = NULL;
    SDL_Surface* tempSurface = NULL;

    if((t = IMG_Load(inFile)) == NULL) return NULL;

    outSurface = SDL_DisplayFormatAlpha(t);
    SDL_FreeSurface(t);

    return outSurface;
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
