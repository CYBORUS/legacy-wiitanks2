#ifndef _BUILDMAPMODULE_H
#define _BUILDMAPMODULE_H

#include "EngineModule.h"
#include "TestModule.h"
#include <SDL.h>

class BuildMapModule : public EngineModule
{
    public:
        BuildMapModule();
        virtual ~BuildMapModule();

        //module operation
        bool onInit();
        void onLoop();
        void onCleanup();
        EngineModule* getNextModule();


    private:
        void onMouseMove(int inX, int inY, int inRelX, int inRelY, bool inLeft,
            bool inRight, bool inMiddle);
        void onLButtonDown(int inX, int inY);

        EngineModule* mNext;
        StaticLayer* mMouse;
        StaticLayer* mTileset;
        StaticLayer* mBackground;
        SDL_Rect dest;
        SDL_Rect src;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int tileMap[50][50]; //Define the map

        //RGB mask values
        Uint32 rmask;
        Uint32 gmask;
        Uint32 bmask;
        Uint32 amask;
};



#endif
