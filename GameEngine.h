#ifndef _GAMEENGINE_H
#define	_GAMEENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <sstream>
#include "AnimatedLayer.h"
#include "EngineModule.h"
#include "ScreenLayer.h"
#include "StaticLayer.h"
#include "TextLayer.h"

#define ENGINE_FPS 30
#define NEXT_FRAME 33

class EngineModule;

class GameEngine
{
    public:
        GameEngine();
        virtual ~GameEngine();

        bool start(EngineModule* inModule);
        void addLayer(VideoLayer* inLayer);
        void removeLayer(VideoLayer* inLayer);

        void onMinimize();
        void onRestore();
        void onResize(int inWidth, int inHeight);
        void onExpose();
        void onExit();

        bool mRunning;
        ScreenLayer mWindow;

    private:
        /// engine loop
        bool onInit();
        inline void onRender();
        void onCleanup();
        void onMusicEnd();

        SDL_Surface* mWindowIcon;
        SDL_Joystick* mJoystick;
};

#endif
