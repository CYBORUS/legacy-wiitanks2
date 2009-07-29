#ifndef _BEGINMODULE_H
#define	_BEGINMODULE_H

#include "EngineModule.h"
#include "TestModule.h"
#include <SDL.h>

class BeginModule : public EngineModule
{
    public:
        BeginModule();
        virtual ~BeginModule();

        /// module operation
        bool onInit();
        void onLoop();
        void onCleanup();
        EngineModule* getNextModule();
        void setNextModule(EngineModule* next);
        void setEngine(GameEngine* inEngine);

    private:
        void onMouseMove(int inX, int inY, int inRelX, int inRelY, bool inLeft,
            bool inRight, bool inMiddle);
        void onLButtonDown(int inX, int inY);

        EngineModule* mNext;
        StaticLayer* mMouse;
        StaticLayer* mBackground;
        SDL_Rect dest;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int AlphaValue;
        int incDec; //whether alphaValue should be incremented or decremented
        int mPauseTime;

};

#endif

