#include "BeginModule.h"
using namespace std;

#define PAUSE_TIME 3

BeginModule::BeginModule()
{
    mMouse = NULL;
    mBackground = NULL;
    mNext = NULL;
    picSurface = NULL;
    tempSurface = NULL;
    AlphaValue = 0;
    incDec = 1;
    mPauseTime = 0;



    dest.x = 0;
    dest.y = 0;

    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    }
    else
    {
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    }
}

BeginModule::~BeginModule()
{
}

bool BeginModule::onInit()
{

    mBackground = new VideoLayer();

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


    mMouse = new VideoLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    mEngine->addLayer(mBackground);
    mEngine->addLayer(mMouse);


    mNext = new BuildMapModule();
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
    SDL_FillRect(mBackground->surface, 0, SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0));


    SDL_BlitSurface(tempSurface, NULL, mBackground->surface, NULL);
    SDL_FillRect(tempSurface, 0, SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0));
    SDL_FreeSurface(tempSurface);

    AlphaValue += incDec * 5;

    if(AlphaValue >= 255)
    {
        if (mPauseTime <= 0)
        {
            AlphaValue = 255;
            mPauseTime = SDL_GetTicks() + (1000 * PAUSE_TIME);
            incDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            mPauseTime = 0;
            incDec = -1;
        }
    }
    else if (AlphaValue <= 0)
    {
        if (mPauseTime <= 0)
        {
            AlphaValue = 0;
            mPauseTime = SDL_GetTicks() + 1000;
            incDec = 0;
        }

        if (SDL_GetTicks() > mPauseTime)
        {
            mEngine->onExit();
        }
    }

    SDL_Delay(10);

}

EngineModule* BeginModule::getNextModule()
{
    return mNext;
}

void BeginModule::onCleanup()
{

    delete mBackground;
    delete mMouse;
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
    mEngine->onExit();
}
