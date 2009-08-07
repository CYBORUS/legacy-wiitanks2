#ifndef _BUILDMAPMODULE_H
#define _BUILDMAPMODULE_H

#include <sstream>
#include <iostream>
using namespace std;

#include <cmath>
#include <SDL.h>
#include <SDL_rotozoom.h>
#include "EngineModule.h"
#include "TestModule.h"
#include "Bullet.h"
#include "Tank.h"

#define MAP_SIZE 50
#define NUM_STEPS 360


struct ActiveTank
{
    Tank* tank;
    ActiveTank* next;
    VideoLayer* layer;
};

class BuildMapModule : public EngineModule
{
    public:
        BuildMapModule();
        virtual ~BuildMapModule();

        //module operation
        bool onInit();
        void onLoop();
        void onFrame();
        void onCleanup();
        SDL_Surface* getCanvas();
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
        ActiveTank* mTanks;
        RotatedGraphic* mTankGraphics;
        RotatedGraphic* mTurretGraphics;

        Bullet* mBullet;


        VideoLayer* temp;
        SDL_Rect mDest;
        SDL_Rect mSrc;
        SDL_Rect* tempRect;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int tileMap[MAP_SIZE][MAP_SIZE]; //Define the map
        double mAngle;
        Mix_Chunk* mShot;
        Mix_Music* mMusic;

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
