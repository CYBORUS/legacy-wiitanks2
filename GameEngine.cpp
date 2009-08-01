#include "GameEngine.h"
using namespace std;

Mask GameEngine::mask;

GameEngine::GameEngine()
{
    mWindowIcon = NULL;
    mJoystick = NULL;
    mCanvas = NULL;
    mCanvasTwo = NULL;
    mAudio = true;
    mCamera.x = 0;
    mCamera.y = 0;
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
    EngineModule* d = NULL;

    if (!onInit()) return false;

    mNextFrame = SDL_GetTicks() + NEXT_FRAME;

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

        mCanvas = em->getCanvas();

        mCanvasTwo = SDL_DisplayFormat(mCanvas);

        while (mRunning)
        {
            while (SDL_PollEvent(&event)) em->onEvent(&event);
            em->onLoop();
            if (SDL_GetTicks() > mNextFrame)
            {
                em->onFrame();
                mNextFrame += NEXT_FRAME;
            }
            onRender();

            SDL_Delay(1); // prevent CPU abuse
        }

        mWindow.next = NULL;
        em->onCleanup();
        //SDL_FreeSurface(mCanvas);
        SDL_FreeSurface(mCanvasTwo);

        d = em;
        em = em->getNextModule();
        delete d;
    }
    onCleanup();
    return true;
}

bool GameEngine::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if (TTF_Init() == -1) return false;
    if (!mWindow.setVideoMode()) return false;

    mCamera.w = mWindow.surface->w;
    mCamera.h = mWindow.surface->h;

    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        GameEngine::mask.red   = 0xff000000;
        GameEngine::mask.green = 0x00ff0000;
        GameEngine::mask.blue  = 0x0000ff00;
        GameEngine::mask.alpha = 0x000000ff;
    }
    else
    {
        GameEngine::mask.red   = 0x000000ff;
        GameEngine::mask.green = 0x0000ff00;
        GameEngine::mask.blue  = 0x00ff0000;
        GameEngine::mask.alpha = 0xff000000;
    }

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
    Uint16 audioFormat = MIX_DEFAULT_FORMAT;
    int audioChannels = 2;
    int audioBuffers = 256;

    if (mAudio && Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers))
    {
        mAudio = false;
        cerr << "Mix_OpenAudio: " << Mix_GetError() << endl;
        cerr << "Unable to open audio!\n";
    }

    return true;
}

inline void GameEngine::onRender()
{
    VideoLayer* iterator = mWindow.next;

    SDL_BlitSurface(mCanvas, NULL, mCanvasTwo, NULL);
    while (iterator != NULL && iterator->priority < PRIORITY_GUI)
    {
        SDL_BlitSurface(iterator->surface, iterator->clip, mCanvasTwo,
            &iterator->location);
        iterator = iterator->next;
    }

    SDL_BlitSurface(mCanvasTwo, &mCamera, mWindow.surface, NULL);

    while (iterator != NULL)
    {
        SDL_BlitSurface(iterator->surface, iterator->clip, mWindow.surface,
            &iterator->location);
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

    if (mAudio) Mix_CloseAudio();

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

void GameEngine::setCanvas(SDL_Surface* inCanvas)
{
    mCanvas = inCanvas;
}

SDL_Rect* GameEngine::setCamera(int inX, int inY)
{
    mCamera.x = inX;
    mCamera.y = inY;

    if (mCamera.x < 0)
    {
        mCamera.x = 0;
    }
    else if (mWindow.surface->w + mCamera.x > mCanvas->w)
    {
        mCamera.x = mCanvas->w - mWindow.surface->w;
    }

    if (mCamera.y < 0)
    {
        mCamera.y = 0;
    }
    else if (mWindow.surface->h + mCamera.y > mCanvas->h)
    {
        mCamera.y = mCanvas->h - mWindow.surface->h;
    }

    return &mCamera;
}

SDL_Rect* GameEngine::moveCamera(int inX, int inY)
{
    return setCamera(mCamera.x + inX, mCamera.y + inY);
}

SDL_Rect* GameEngine::getCamera()
{
    return &mCamera;
}

Mix_Music* GameEngine::loadMusic(const char* inFile)
{
    if (!mAudio) return NULL;
    return Mix_LoadMUS(inFile);
}

void GameEngine::freeMusic(Mix_Music* inMusic)
{
    if (inMusic != NULL) Mix_FreeMusic(inMusic);
}

Mix_Chunk* GameEngine::loadSound(const char* inFile)
{
    if (!mAudio) return NULL;
    return Mix_LoadWAV(inFile);
}

void GameEngine::freeSound(Mix_Chunk* inSound)
{
    if (inSound != NULL) Mix_FreeChunk(inSound);
}

void GameEngine::playSound(Mix_Chunk* inSound)
{
    if (!mAudio) return;
    Mix_PlayChannel(-1, inSound, 0);
}
