#ifndef _ROTATEDGRAPHIC_H
#define _ROTATEDGRAPHIC_H

#include "SDL_Tools.h"
#include <string>
using namespace std;

#define DEGREES 360

class RotatedGraphic
{
    public:
        RotatedGraphic(const char* inFile, int inRotations);
        virtual ~RotatedGraphic();

        Surface getSurface(int inIndex);

    private:
        string mName;
        int mRotations;
        Surface* mSurfaces;
};

#endif
