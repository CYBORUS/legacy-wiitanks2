#ifndef _LAYER_H
#define	_LAYER_H

#include <SDL.h>

struct Layer
{
    int priority;
    SDL_Surface* surface;
    Layer* next;
};

#endif
