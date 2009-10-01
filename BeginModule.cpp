#include "BeginModule.h"
using namespace std;

#define PAUSE_TIME 3

BeginModule::BeginModule()
{
    mMouse = NULL;
    mBackground = NULL;
    mPic = NULL;
    mTempSurface = NULL;
    mAlphaValue = 0;
    mIncDec = 1;
    mPauseTime = 0;



    mDest.x = 0;
    mDest.y = 0;
}

BeginModule::~BeginModule()
{
}

bool BeginModule::onInit()
{
    mBackground = new VideoLayer();

    Surface t = GameEngine::newSurface(SDL_GetVideoSurface()->w,
        SDL_GetVideoSurface()->h);

    mBackground->surface = GameEngine::newSurface(SDL_GetVideoSurface()->w,
        SDL_GetVideoSurface()->h);

    mPic = VideoLayer::getImage("images/presenting.jpg");
    SDL_BlitSurface(mPic, NULL, t, &mDest);
    mTempSurface = SDL_DisplayFormat(t);
    SDL_FreeSurface(t);

    SDL_SetAlpha(mBackground->surface, SDL_SRCALPHA, 255);
    SDL_BlitSurface(mTempSurface, NULL, mBackground->surface, &mDest);
    mBackground->priority = PRIORITY_BACKGROUND;

    SDL_ShowCursor(SDL_DISABLE);

    if ((mTempSurface = GameEngine::newSurface(SDL_GetVideoSurface()->w,
        SDL_GetVideoSurface()->h)) == NULL)
    {
        cerr << "creation failed" << endl;
        exit(1);
    }

    return true;
}

void BeginModule::onFrame()
{

    //SDL_FillRect( mTempSurface, 0, SDL_MapRGBA(mTempSurface->format, 0, 0, 0, 0) );

    SDL_BlitSurface(mPic, NULL, mTempSurface, &mDest);

    SDL_SetAlpha(mTempSurface, SDL_SRCALPHA | SDL_RLEACCEL, mAlphaValue);
    SDL_FillRect(mBackground->surface, 0, SDL_MapRGBA(mTempSurface->format, 0, 0, 0, 0));


    SDL_BlitSurface(mTempSurface, NULL, mBackground->surface, NULL);
    SDL_FillRect(mTempSurface, 0, SDL_MapRGBA(mTempSurface->format, 0, 0, 0, 0));
    //SDL_FreeSurface(mTempSurface);

    mAlphaValue += mIncDec * 5;

    if(mAlphaValue >= 255)
    {
        if (mPauseTime <= 0)
        {
            mAlphaValue = 255;
            mPauseTime = SDL_GetTicks() + (1000 * PAUSE_TIME);
            mIncDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            mPauseTime = 0;
            mIncDec = -1;
        }
    }
    else if (mAlphaValue <= 0)
    {
        if (mPauseTime <= 0)
        {
            mAlphaValue = 0;
            mPauseTime = SDL_GetTicks() + 1000;
            mIncDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            GameEngine::onExit();
        }
    }
}

EngineModule* BeginModule::getNextModule()
{
    return new BuildMapModule();
}

void BeginModule::onCleanup()
{

    delete mBackground;
    delete mMouse;
}

void BeginModule::onLButtonDown(int inX, int inY)
{
    GameEngine::onExit();
}

Surface BeginModule::getCanvas()
{
    return mBackground->surface;
}
