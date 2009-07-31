#ifndef _BUILDMAPMODULE_H
#define _BUILDMAPMODULE_H

#include <sstream>
using namespace std;

#include "EngineModule.h"
#include "TestModule.h"
#include "SDL_rotozoom.h"
#include <cmath>
#include <SDL.h>

#define MAP_SIZE 50
#define NUM_STEPS 360

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
        void onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        void onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        void onRButtonDown(int inX, int inY);

        EngineModule* mNext;
        VideoLayer* mMouse;
        VideoLayer* mTileset;
        VideoLayer* mBackground;
        VideoLayer* mTurret;


        VideoLayer* temp;
        SDL_Rect dest;
        SDL_Rect src;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int tileMap[MAP_SIZE][MAP_SIZE]; //Define the map
        double oldAngle;

        stringstream s;

        //to control scroll movement
        int xMove;
        int yMove;

        //RGB mask values
        Uint32 rmask;
        Uint32 gmask;
        Uint32 bmask;
        Uint32 amask;
};



#endif
