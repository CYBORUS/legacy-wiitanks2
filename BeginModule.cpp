#include "BeginModule.h"
using namespace std;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

#define PAUSE_TIME 3

BeginModule::BeginModule()
{
    mChannel = -1;
    mMusic = NULL;
    mSound = NULL;
    mMouse = NULL;
    mBackground = NULL;
    mFPS = NULL;
    mFrames = 0;
    mJS1 = NULL;
    mNext = NULL;
    picSurface = NULL;
    tempSurface = NULL;
    AlphaValue = 0;
    incDec = 1;
    mPauseTime = -1;



    dest.x = 0;
    dest.y = 0;
}

BeginModule::~BeginModule()
{
}

bool BeginModule::onInit()
{
    mBackground = new StaticLayer();

    SDL_Surface* t = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
                                mEngine->mWindow.mWidth, mEngine->mWindow.mHeight,
                                32, rmask, gmask, bmask, amask);

    mBackground->surface = SDL_DisplayFormat(t);

    picSurface = VideoLayer::getImage("images/presenting.jpg");
    SDL_BlitSurface(picSurface, NULL, t, &dest);
    tempSurface = SDL_DisplayFormat(t);
    SDL_FreeSurface(t);

    SDL_SetAlpha(mBackground->surface, SDL_SRCALPHA, 255);
    SDL_BlitSurface(tempSurface, NULL, mBackground->surface, &dest);
    mBackground->priority = PRIORITY_BACKGROUND;


    mMouse = new StaticLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    mEngine->addLayer(mBackground);
    mEngine->addLayer(mMouse);

    mNext = new TestModule();
    return true;
}

void BeginModule::onLoop()
{
    SDL_Surface* t = NULL;

    if ((t = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
                                mEngine->mWindow.mWidth, mEngine->mWindow.mHeight,
                                32, rmask, gmask, bmask, amask)) == NULL)
    {
        cerr << "creation failed" << endl;
        exit(1);
    }

    tempSurface = SDL_DisplayFormat(t);
    SDL_FreeSurface(t);

    SDL_FillRect( tempSurface, 0, SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0) );

    SDL_BlitSurface(picSurface, NULL, tempSurface, &dest);

    SDL_SetAlpha(tempSurface, SDL_SRCALPHA, AlphaValue);
    SDL_FillRect(mEngine->mWindow.next->surface, 0, SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0));


    SDL_BlitSurface(tempSurface, NULL, mEngine->mWindow.next->surface, NULL);
    SDL_FillRect(tempSurface, 0, SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0));
    SDL_FreeSurface(tempSurface);

    AlphaValue += incDec * 5;

    if(AlphaValue >= 255)
    {
        if (mPauseTime < 0)
        {
            AlphaValue = 255;
            mPauseTime = SDL_GetTicks() + (1000 * PAUSE_TIME);
            incDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            mPauseTime = -1;
            incDec = -1;
        }
    }
    else if (AlphaValue <= 0)
    {
        if (mPauseTime < 0)
        {
            AlphaValue = 0;
            mPauseTime = SDL_GetTicks() + 1000;
            incDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            mEngine->mRunning = false;
        }
    }

    SDL_Delay(10);

}

EngineModule* BeginModule::getNextModule()
{
    return mNext;
}

void BeginModule::setNextModule(EngineModule* next)
{
    mNext = next;
}

void BeginModule::onCleanup()
{
    if (mMusic != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(mMusic);
        mMusic = NULL;
    }

    delete mBackground;
    delete mMouse;
    delete mText;
    delete mFPS;
    delete mJS1;
    delete mJS2;
    delete mJS3;
    delete mYoshi;
}


void BeginModule::onMouseMove(int inX, int inY, int inRelX, int inRelY,
    bool inLeft, bool inRight, bool inMiddle)
{
    if (mMouse == NULL) return;
    mMouse->setLocation(inX, inY);
}

void BeginModule::onLButtonDown(int inX, int inY)
{
    if (mEngine == NULL) return;
    mEngine->mRunning = false;
}

void BeginModule::onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue)
{
}

void BeginModule::onJoyButtonDown(Uint8 inWhich, Uint8 inButton)
{
}

void BeginModule::onJoyButtonUp(Uint8 inWhich, Uint8 inButton)
{
}

void BeginModule::onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue)
{
}

void BeginModule::onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
    Sint16 inYRel)
{
}
