#include "GameEngine.h"
using namespace std;

GameEngine::GameEngine()
{
    mWindowIcon = NULL;
    mJoystick = NULL;
}

GameEngine::~GameEngine()
{
}

void GameEngine::addLayer(VideoLayer* inLayer)
{
    if (inLayer == NULL) return;
    VideoLayer* sl = mWindow.next;

    if (sl == NULL)
    {
        mWindow.next = inLayer;
        return;
    }
    else if (inLayer->priority < sl->priority)
    {
        inLayer->next = sl;
        mWindow.next = inLayer;
        return;
    }

    while (sl->next != NULL && inLayer->priority >= sl->next->priority)
        sl = sl->next;

    inLayer->next = sl->next;
    sl->next = inLayer;
}

void GameEngine::removeLayer(VideoLayer* inLayer)
{
    if (inLayer == NULL) return;

    if (mWindow.next == inLayer)
    {
        mWindow.next = inLayer->next;
        inLayer->next = NULL;
        return;
    }

    VideoLayer* sl = mWindow.next;
    while (sl->next != NULL && sl->next != inLayer) sl = sl->next;
    if (sl->next == inLayer)
    {
        sl->next = inLayer->next;
        inLayer->next = NULL;
    }
}

bool GameEngine::start(EngineModule* inModule)
{
    EngineModule* em = inModule;

    if (!onInit()) return false;

    SDL_Event event;

    while (em != NULL)
    {
        mRunning = true;

        em->setEngine(this);
        if (!em->onInit())
        {
            em = NULL;
            mRunning = false;
            break;
        }

        while (mRunning)
        {
            while (SDL_PollEvent(&event)) em->onEvent(&event);
            em->onLoop();
            onRender();

            SDL_Delay(1); // prevent CPU abuse
        }

        mWindow.next = NULL;
        em->onCleanup();
        em = em->next();
    }
    onCleanup();
    return true;
}

bool GameEngine::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if (TTF_Init() == -1) return false;
    if (!mWindow.setVideoMode()) return false;
    mWindow.next = NULL;

    if (SDL_NumJoysticks() > 0)
    {
        SDL_JoystickEventState(SDL_ENABLE);
        mJoystick = SDL_JoystickOpen(0);
        cerr << "a " << SDL_JoystickNumAxes(mJoystick)
            << " b " << SDL_JoystickNumButtons(mJoystick)
            << " l " << SDL_JoystickNumBalls(mJoystick)
            << " h " << SDL_JoystickNumHats(mJoystick)
            << endl;
    }

    mWindowIcon = VideoLayer::getImage("nexus.png");
    SDL_WM_SetIcon(mWindowIcon, NULL);
    SDL_WM_SetCaption("Zero2D","");

    int audioRate = 22050;
    Uint16 audioFormat = AUDIO_S16;
    int audioChannels = 2;
    int audioBuffers = 4096;

//    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers))
//    {
//        cerr << "Unable to open audio!\n";
//        return false;
//    }

    return true;
}

//void GameEngine::onLoop()
//{
//    stringstream s;
//
//    mFrames++;
//
//    if (SDL_GetTicks() > mNextFrame)
//    {
//        mNextFrame += NEXT_FRAME * 3;
//        mYoshi->update();
//    }
//
//    if (SDL_GetTicks() > mNextSecond)
//    {
//        s << mFrames << " FPS";
//        mFPS->setText(s.str().c_str());
//        mNextSecond = SDL_GetTicks() + 1000;
//        mFrames = 0;
//    }
//}

inline void GameEngine::onRender()
{
    VideoLayer* iterator = mWindow.next;
    while (iterator != NULL)
    {
        //if (iterator->surface == NULL) exit(1);
        SDL_BlitSurface(iterator->surface, iterator->clip, mWindow.surface,
            iterator->location);
        iterator = iterator->next;
    }
    SDL_Flip(mWindow.surface);
}

void GameEngine::onCleanup()
{
    SDL_ShowCursor(SDL_ENABLE);
    SDL_FreeSurface(mWindowIcon);
    mWindowIcon = NULL;

    if (mJoystick != NULL)
    {
        SDL_JoystickClose(mJoystick);
        mJoystick = NULL;
    }

    //Mix_CloseAudio();

    TTF_Quit();
    SDL_Quit();
}

void GameEngine::onExit()
{
    mRunning = false;
}

void GameEngine::onMinimize()
{
}

void GameEngine::onRestore()
{
}

void GameEngine::onResize(int inWidth, int inHeight)
{
}

void GameEngine::onExpose()
{
}
