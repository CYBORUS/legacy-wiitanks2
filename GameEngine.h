#ifndef _GAMEENGINE_H
#define	_GAMEENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include "AnimatedLayer.h"
#include "EngineModule.h"
#include "ScreenLayer.h"
#include "VideoLayer.h"
#include "TextLayer.h"

#define ENGINE_FPS 30
#define NEXT_FRAME 25

struct Mask
{
    Uint32 red;
    Uint32 green;
    Uint32 blue;
    Uint32 alpha;
};

class EngineModule;

class GameEngine
{
    public:
        GameEngine();
        virtual ~GameEngine();

        bool start(EngineModule* inModule);
        void addLayer(VideoLayer* inLayer);
        void removeLayer(VideoLayer* inLayer);
        void setCanvas(SDL_Surface* inCanvas);
        SDL_Rect* setCamera(int inX, int inY);
        SDL_Rect* moveCamera(int inX, int inY);
        SDL_Rect* getCamera();
        void changeSurface(SDL_Rect* inOld, SDL_Rect* inNew, VideoLayer* inLayer);
        void buildSurfaces();

        Mix_Music* loadMusic(const char* inFile);
        void freeMusic(Mix_Music* inMusic);
        Mix_Chunk* loadSound(const char* inFile);
        void freeSound(Mix_Chunk* inSound);
        void playSound(Mix_Chunk* inSound);

        void onMinimize();
        void onRestore();
        void onResize(int inWidth, int inHeight);
        void onExpose();
        void onExit();

        static Mask mask;

        ScreenLayer mWindow;

    private:
        /// engine loop
        bool onInit();
        inline void onRender();
        void onCleanup();
        void onMusicEnd();

        bool mAudio;
        bool mRunning;
        unsigned int mNextFrame;
        unsigned int mCurrentFrame;
        SDL_Surface* mWindowIcon;
        SDL_Joystick* mJoystick;
        SDL_Surface* mCanvas;
        SDL_Surface* mCanvasTwo;
        SDL_Rect mCamera;
};

#endif
