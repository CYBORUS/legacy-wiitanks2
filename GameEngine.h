#ifndef _GAMEENGINE_H
#define	_GAMEENGINE_H

#include "SDL_Tools.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "AnimatedLayer.h"
#include "EngineModule.h"
#include "VideoLayer.h"
#include "TextLayer.h"
#include "Preferences.h"

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
        static bool start(EngineModule* inModule);
        static void addLayer(VideoLayer* inLayer);
        static void removeLayer(VideoLayer* inLayer);
        static void setCanvas(Surface inCanvas);
        static SDL_Rect* setCamera(int inX, int inY);
        static SDL_Rect* moveCamera(int inX, int inY);
        static SDL_Rect* getCamera();
        static void changeSurface(SDL_Rect* inOld, SDL_Rect* inNew,
            VideoLayer* inLayer);
        static void buildSurfaces();

        static Mix_Music* loadMusic(const char* inFile);
        static void freeMusic(Mix_Music* inMusic);
        static Mix_Chunk* loadSound(const char* inFile);
        static void freeSound(Mix_Chunk* inSound);
        static void playSound(Mix_Chunk* inSound);
        static void musicDone();

        static void onMinimize();
        static void onRestore();
        static void onResize(int inWidth, int inHeight);
        static void onExpose();
        static void onExit();

        static Surface newSurface(int inWidth, int inHeight);

        static Mask mask;

    private:
        /// engine loop
        static bool onInit();
        static inline void onRender();
        static void onCleanup();
        static void onMusicEnd();

        static bool mAudio;
        static bool mRunning;
        static unsigned int mNextFrame;
        static unsigned int mCurrentFrame;
        static Surface mWindowIcon;
        static SDL_Joystick* mJoystick;
        static Surface mCanvas;
        static Surface mCanvasTwo;
        static SDL_Rect mCamera;
        static VideoLayer mWindow;
};

#endif
