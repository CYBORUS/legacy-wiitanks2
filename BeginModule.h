#ifndef _BEGINMODULE_H
#define	_BEGINMODULE_H

#include "EngineModule.h"
#include "TestModule.h"
#include <sdl.h>

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
        void onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue);
        void onJoyButtonDown(Uint8 inWhich, Uint8 inButton);
        void onJoyButtonUp(Uint8 inWhich, Uint8 inButton);
        void onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue);
        void onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
            Sint16 inYRel);

        EngineModule* mNext;
        StaticLayer* mMouse;
        StaticLayer* mBackground;
        SDL_Rect dest;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
        int AlphaValue;
        int incDec; //whether alphaValue should be incremented or decremented
        int mPauseTime;

        TextLayer* mText;
        TextLayer* mFPS;
        TextLayer* mJS1;
        TextLayer* mJS2;
        TextLayer* mJS3;
        AnimatedLayer* mYoshi;
        Mix_Music* mMusic;
        Mix_Chunk* mSound;
        int mChannel;
        int mFrames;
        unsigned int mNextSecond;
        unsigned int mNextFrame;
};

#endif

