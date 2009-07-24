#ifndef _SURFACETOOLS_H
#define	_SURFACETOOLS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

SDL_Surface* newImage(const char* inFile)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(inFile)) == NULL) return NULL;

    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool draw(SDL_Surface* inTarget, SDL_Surface* inSurface, int inX, int inY)
{
    if (inTarget == NULL || inSurface == NULL) return false;

    SDL_Rect DestR;

    DestR.x = inX;
    DestR.y = inY;

    SDL_BlitSurface(inSurface, NULL, inTarget, &DestR);

    return true;
}

#endif
