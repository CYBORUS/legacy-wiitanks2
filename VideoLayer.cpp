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

Surface VideoLayer::getImage(const char* inFile)
{
    Surface t = NULL;
    Surface outSurface = NULL;

    if((t = IMG_Load(inFile)) == NULL)
    {
        cerr << "Failed to load " << inFile << endl;
        return NULL;
    }

    outSurface = SDL_DisplayFormatAlpha(t);
    SDL_FreeSurface(t);

    return outSurface;
}

void VideoLayer::setLocation(int inX, int inY)
{
    location.x = inX;
    location.y = inY;
}

//void VideoLayer::overlay(Surface inTarget, Surface inSurface)
//{
//    if (inTarget == NULL || inSurface == NULL) return;
//    SDL_BlitSurface(inSurface, NULL, inTarget, NULL);
//}
//
//void VideoLayer::overlay(Surface inTarget, Surface inSurface,
//    SDL_Rect* inLocation)
//{
//    if (inTarget == NULL || inSurface == NULL) return;
//    SDL_BlitSurface(inSurface, NULL, inTarget, inLocation);
//}
//
//void VideoLayer::overlay(Surface inTarget, Surface inSurface,
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
