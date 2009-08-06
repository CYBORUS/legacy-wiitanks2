#include <SDL_rotozoom.h>
#include "RotatedGraphic.h"
#include "VideoLayer.h"

RotatedGraphic::RotatedGraphic(const char* inFile, int inRotations)
{
    mRotations = inRotations;
    mSurfaces = new SDL_Surface*[mRotations];

    mSurfaces[0] = VideoLayer::getImage(inFile);

    for (int i = 1; i < mRotations; i++)
    {
        double angle = i * DEGREES / mRotations;
        mSurfaces[i] = rotozoomSurface(mSurfaces[0], angle, 1.0, 1);
    }
}

RotatedGraphic::~RotatedGraphic()
{
    delete [] mSurfaces;
}

SDL_Surface* RotatedGraphic::getSurface(int inIndex)
{
    if (inIndex < 0 || inIndex >= mRotations) return NULL;
    return mSurfaces[inIndex];
}
