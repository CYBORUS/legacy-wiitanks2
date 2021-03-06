#ifndef _TESTMODULE_H
#define	_TESTMODULE_H

#include "EngineModule.h"

class TestModule : public EngineModule
{
    public:
        TestModule();
        virtual ~TestModule();

        /// module operation
        bool onInit();
        void onLoop();
        void onFrame();
        void onCleanup();
        EngineModule* getNextModule();
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
        VideoLayer* mMouse;
        VideoLayer* mTest;
        TextLayer* mText;
        TextLayer* mFPS;
        TextLayer* mJS1;
        TextLayer* mJS2;
        TextLayer* mJS3;
        TextLayer* mJS4;
        TextLayer* mJS5;
        TextLayer* mJS6;
        AnimatedLayer* mYoshi;
        Mix_Music* mMusic;
        Mix_Chunk* mSound;
        int mChannel;
        int mFrames;
        unsigned int mNextSecond;
        unsigned int mNextFrame;
};

#endif
