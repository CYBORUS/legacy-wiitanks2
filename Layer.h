#ifndef _LAYER_H
#define	_LAYER_H

#include "SDL_Tools.h"

struct Layer
{
    int priority;
    Surface surface;
    Layer* next;
};

#endif
