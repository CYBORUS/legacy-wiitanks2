#include <SDL_rotozoom.h>
#include "RotatedGraphic.h"
#include "VideoLayer.h"

#include <iostream>
using namespace std;

RotatedGraphic::RotatedGraphic(const char* inFile, int inRotations)
{
    mRotations = inRotations;
    mSurfaces = new SDL_Surface*[mRotations];
    double angle;

    mSurfaces[0] = VideoLayer::getImage(inFile);

    for (int i = 1; i < mRotations; i++)
    {
        angle = i * DEGREES / mRotations;
        mSurfaces[i] = rotozoomSurface(mSurfaces[0], angle, 1.0, 1);
    }
}

RotatedGraphic::~RotatedGraphic()
{
    for (int i = 0; i < mRotations; i++) SDL_FreeSurface(mSurfaces[i]);

    delete [] mSurfaces;
}

SDL_Surface* RotatedGraphic::getSurface(int inIndex)
{
    if (inIndex < 0 || inIndex >= mRotations)
    {
        cerr << "yep" << endl;
        return NULL;
    }
    return mSurfaces[inIndex];
}
