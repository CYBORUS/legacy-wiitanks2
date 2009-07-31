#ifndef _BEGINMODULE_H
#define	_BEGINMODULE_H

#include "EngineModule.h"
#include "BuildMapModule.h"
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

    private:
        void onMouseMove(int inX, int inY, int inRelX, int inRelY, bool inLeft,
            bool inRight, bool inMiddle);
        void onLButtonDown(int inX, int inY);

        EngineModule* mNext;
        VideoLayer* mMouse;
        VideoLayer* mBackground;
        SDL_Rect dest;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int AlphaValue;
        int incDec; //whether alphaValue should be incremented or decremented
        unsigned int mPauseTime;

        //RGB mask values
        Uint32 rmask;
        Uint32 gmask;
        Uint32 bmask;
        Uint32 amask;

};

#endif

