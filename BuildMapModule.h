#ifndef _BUILDMAPMODULE_H
#define _BUILDMAPMODULE_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "SDL_Tools.h"
#include <SDL_rotozoom.h>
#include "EngineModule.h"
#include "TestModule.h"
#include "Bullet.h"
#include "Tank.h"
#include "GameMap.h"
#include "CollisionEngine.h"
using namespace std;

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
        Surface getCanvas();
        EngineModule* getNextModule();

    private:
        void onMouseMove(int inX, int inY, int inRelX, int inRelY, bool inLeft,
            bool inRight, bool inMiddle);
        void onLButtonDown(int inX, int inY);
        void onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        void onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        void onRButtonDown(int inX, int inY);
        void onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue);

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
        GameMap* mMap;
        double mAngle;
        Mix_Chunk* mShot;
        Mix_Music* mMusic;

        unsigned int mNextSecond;
        TextLayer* mFPS;
        int mFrames;

        //to control scroll movement
        int mMoveX;
        int mMoveY;
};



#endif
