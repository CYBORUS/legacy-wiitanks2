#ifndef _BEGINMODULE_H
#define	_BEGINMODULE_H

#include <iostream>
using namespace std;

#include "GameEngine.h"
#include "EngineModule.h"
#include "BuildMapModule.h"
#include "Preferences.h"
#include "SDL_Tools.h"

class BeginModule : public EngineModule
{
    public:
        BeginModule();
        virtual ~BeginModule();

        /// module operation
        bool onInit();
        void onFrame();
        void onCleanup();
        EngineModule* getNextModule();
        Surface getCanvas();

    private:
        void onLButtonDown(int inX, int inY);

        VideoLayer* mMouse;
        VideoLayer* mBackground;
        SDL_Rect mDest;
        Surface mPic;
        Surface mTempSurface;
        int mAlphaValue;
        int mIncDec; //whether alphaValue should be incremented or decremented
        unsigned int mPauseTime;

};

#endif

