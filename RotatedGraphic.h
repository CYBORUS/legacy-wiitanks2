#ifndef _ROTATEDGRAPHIC_H
#define _ROTATEDGRAPHIC_H

#include <SDL.h>
#include <string>
#include <cmath>
using namespace std;

#define DEGREES 360

class RotatedGraphic
{
    public:
        RotatedGraphic(const char* inFile, int inRotations);
        virtual ~RotatedGraphic();

        SDL_Surface* getSurface(int inIndex);

    private:
        string mName;
        int mRotations;
        SDL_Surface** mSurfaces;
};

#endif
