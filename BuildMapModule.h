#ifndef _BUILDMAPMODULE_H
#define _BUILDMAPMODULE_H

#include "EngineModule.h"
#include "TestModule.h"

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
        StaticLayer* mBackground;
        SDL_Rect dest;
        SDL_Surface* picSurface;
        SDL_Surface* tempSurface;
};



#endif
