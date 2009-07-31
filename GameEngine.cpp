#include "GameEngine.h"
using namespace std;

Mask GameEngine::mask;

GameEngine::GameEngine()
{
    cerr << "??" << endl;
    mWindowIcon = NULL;
    mJoystick = NULL;
    mCanvas = NULL;
    mCanvasTwo = NULL;
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
    //SDL_Surface* t = NULL;
    //SDL_Surface* tempSurface = NULL;

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

//    tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 800, 600, 32, rmask, gmask, bmask, amask);
//
//
//    t = SDL_DisplayFormat(tempSurface);
//
//    SDL_FreeSurface(tempSurface);
//
//
//    SDL_Rect dest;
//    dest.x = 0;
//    dest.y = 0;
//
//	SDL_FillRect( t, 0, SDL_MapRGBA(t->format, 0, 0, 0, 0) );
//
//    SDL_BlitSurface(mWindow.surface, NULL, t, &dest);
//    SDL_SetAlpha(t, SDL_SRCALPHA, 128);
//
//    SDL_FillRect( mWindow.surface, 0, SDL_MapRGBA(t->format, 255, 255, 255, 0) );
//
//
//    SDL_BlitSurface(t, NULL, mWindow.surface, &dest);
//    SDL_FreeSurface(t);

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
