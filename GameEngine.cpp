#include "GameEngine.h"
using namespace std;

Mask GameEngine::mask;
ScreenLayer GameEngine::mWindow;
bool GameEngine::mAudio;
bool GameEngine::mRunning;
unsigned int GameEngine::mNextFrame;
unsigned int GameEngine::mCurrentFrame;
SDL_Surface* GameEngine::mWindowIcon;
SDL_Joystick* GameEngine::mJoystick;
SDL_Surface* GameEngine::mCanvas;
SDL_Surface* GameEngine::mCanvasTwo;
SDL_Rect GameEngine::mCamera;

void GameEngine::construct()
{
    mWindowIcon = NULL;
    mJoystick = NULL;
    mCanvas = NULL;
    mCanvasTwo = NULL;
    mAudio = true;
    mCamera.x = 0;
    mCamera.y = 0;

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
    //settings = new GameSettings();
    EngineModule* em = inModule;
    EngineModule* d = NULL;

    if (!onInit()) return false;

    mNextFrame = SDL_GetTicks() + NEXT_FRAME;

    SDL_Event event;

    while (em != NULL)
    {
        mRunning = true;

        if (!em->onInit())
        {
            em = NULL;
            mRunning = false;
            break;
        }

        mCanvas = em->getCanvas();

        mCanvasTwo = SDL_DisplayFormat(mCanvas);

        buildSurfaces(); //do an initial build of all the surfaces
        //SDL_Flip(mWindow.surface);

        while (mRunning)
        {
            while (SDL_PollEvent(&event)) em->onEvent(&event);
            em->onLoop();
            if ((mCurrentFrame = SDL_GetTicks()) > mNextFrame)
            {
                while (mNextFrame <= mCurrentFrame)
                {
                    em->onFrame();
                    mNextFrame += NEXT_FRAME;
                }
                //buildSurfaces();
                //SDL_Flip(mWindow.surface);
                onRender();
            }

            SDL_Delay(1); // prevent CPU abuse
        }

        mWindow.next = NULL;
        em->onCleanup();
        //SDL_FreeSurface(mCanvas);
        SDL_FreeSurface(mCanvasTwo);

        d = em;
        em = em->getNextModule();
        delete d;

        mCamera.x = 0;
        mCamera.y = 0;
    }
    onCleanup();
    return true;
}

bool GameEngine::onInit()
{
    #ifdef _WIN32
        putenv("SDL_VIDEODRIVER=directx");
    #endif

    putenv("SDL_VIDEO_CENTERED=1");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if (TTF_Init() == -1) return false;

    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    // This block is test code to help know what resolutions are supported
    // Should be placed somewhere else once we have a setup screen working
    SDL_Rect** modes;

    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);

    /* Check if there are any modes available */
    if (modes == (SDL_Rect**)0)
    {
        printf("No modes available!\n");
        exit(-1);
    }

    /* Check if our resolution is restricted */
    if (modes == (SDL_Rect**)-1)
    {
        printf("All resolutions available.\n");
    }
    else
    {
        /* Print valid modes */
        printf("Available Modes\n");
        for (int i=0; modes[i]; ++i)
        printf("  %d x %d\n", modes[i]->w, modes[i]->h);
    }

    //end of screen resolution code


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

    //SDL_BlitSurface(mCanvasTwo, &mCamera, mWindow.surface, NULL);
    //buildSurfaces();

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

inline void GameEngine::buildSurfaces()
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

}

void GameEngine::changeSurface(SDL_Rect* inOld, SDL_Rect* inNew, VideoLayer* inLayer)
{
    SDL_Rect newSrc;
    SDL_Rect newDest;
    int wDiff;
    int hDiff;

    VideoLayer* iterator = mWindow.next;

    newDest.x = inOld->x;
    newDest.y = inOld->y;
    newDest.w = inOld->w;
    newDest.h = inOld->h;

    SDL_BlitSurface(mCanvas, inOld, mCanvasTwo, &newDest);

    while (iterator != NULL && iterator->priority < PRIORITY_GUI)
    {
        if (((iterator->location.x + iterator->location.w - 1) >= inOld->x) && (iterator->location.x <= (inOld->x + inOld->w - 1)) &&
            ((iterator->location.y + iterator->location.h - 1) >= inOld->y) && (iterator->location.y <= (inOld->y + inOld->h - 1)))
        {

            newSrc.x = inOld->x - (iterator->location.x);
            newSrc.y = inOld->y - (iterator->location.y);
            wDiff = (iterator->location.x + iterator->location.w) - (inOld->x + inOld->w);
            hDiff = (iterator->location.y + iterator->location.h) - (inOld->y + inOld->h);

            if (newSrc.x < 0) newSrc.x = 0;
            if (newSrc.y < 0) newSrc.y = 0;

            if (wDiff < 0) wDiff = 0;
            if (hDiff < 0) hDiff = 0;

            newSrc.w = iterator->location.w - newSrc.x - newSrc.w;
            newSrc.h = iterator->location.h - newSrc.y - newSrc.h;

            newDest.x = inOld->x + newSrc.x;
            newDest.y = inOld->y + newSrc.y;
            newDest.w = newSrc.w;
            newDest.h = newSrc.h;


            SDL_BlitSurface(iterator->surface, &newSrc, mCanvasTwo,
                &newDest);
        }
        iterator = iterator->next;

    }

    if (inLayer->priority < PRIORITY_GUI)
    {
        SDL_BlitSurface(inLayer->surface, NULL, mCanvasTwo, inNew);
    }

    SDL_BlitSurface(mCanvasTwo, &mCamera, mWindow.surface, NULL);

    while (iterator != NULL)
    {
        if (((iterator->location.x + iterator->location.w - 1) >= inOld->x) && (iterator->location.x <= (inOld->x + inOld->w - 1)) &&
            ((iterator->location.y + iterator->location.h - 1) >= inOld->y) && (iterator->location.y <= (inOld->y + inOld->h - 1)))
        {

            newSrc.x = inOld->x - (iterator->location.x);
            newSrc.y = inOld->y - (iterator->location.y);
            wDiff = (iterator->location.x + iterator->location.w) - (inOld->x + inOld->w);
            hDiff = (iterator->location.y + iterator->location.h) - (inOld->y + inOld->h);

            if (newSrc.x < 0) newSrc.x = 0;
            if (newSrc.y < 0) newSrc.y = 0;

            if (wDiff < 0) wDiff = 0;
            if (hDiff < 0) hDiff = 0;

            newSrc.w = iterator->location.w - newSrc.x - newSrc.w;
            newSrc.h = iterator->location.h - newSrc.y - newSrc.h;

            newDest.x = inOld->x + newSrc.x;
            newDest.y = inOld->y + newSrc.y;
            newDest.w = newSrc.w;
            newDest.h = newSrc.h;


            SDL_BlitSurface(iterator->surface, &newSrc, mWindow.surface,
                &newDest);
        }
        iterator = iterator->next;
    }

    if (inLayer->priority >= PRIORITY_GUI)
    {
        SDL_BlitSurface(inLayer->surface, NULL, mWindow.surface, inNew);
    }
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
