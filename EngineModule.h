#ifndef _ENGINEMODULE_H
#define	_ENGINEMODULE_H

#include "GameEngine.h"



class GameEngine;

class EngineModule
{
    public:
        EngineModule();
        virtual ~EngineModule();

        /// module operation
        virtual bool onInit() = 0;
        virtual void onLoop() = 0;
        virtual void onFrame();
        virtual void onCleanup() = 0;
        virtual EngineModule* getNextModule() = 0;
        void setEngine(GameEngine* inEngine);

        /// input events
        virtual void onEvent(SDL_Event* inEvent);
        virtual void onInputFocus();
        virtual void onInputBlur();
        virtual void onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        virtual void onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        virtual void onMouseFocus();
        virtual void onMouseBlur();
        virtual void onMouseMove(int inX, int inY, int inRelX, int inRelY,
            bool inLeft, bool inRight, bool inMiddle);
        virtual void onMouseWheel(bool inUp, bool inDown);
        virtual void onLButtonDown(int inX, int inY);
        virtual void onLButtonUp(int inX, int inY);
        virtual void onRButtonDown(int inX, int inY);
        virtual void onRButtonUp(int inX, int inY);
        virtual void onMButtonDown(int inX, int inY);
        virtual void onMButtonUp(int inX, int inY);
        virtual void onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue);
        virtual void onJoyButtonDown(Uint8 inWhich, Uint8 inButton);
        virtual void onJoyButtonUp(Uint8 inWhich, Uint8 inButton);
        virtual void onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue);
        virtual void onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
            Sint16 inYRel);
        virtual void onMinimize();
        virtual void onRestore();
        virtual void onResize(int inWidth, int inHeight);
        virtual void onExpose();
        virtual void onExit();
        virtual void onUser(Uint8 inType, int inCode, void* inData1, void* inData2);

    protected:
        GameEngine* mEngine;
};

#endif
