#include "BuildMapModule.h"

//included for rand(), should be removed after development
#include <cstdlib>
#include <iostream>
using namespace std;



int X = MAP_SIZE * 25;
int Y = MAP_SIZE * 25;


BuildMapModule::BuildMapModule()
{
    mMouse = NULL;
    mTileset = NULL;
    mBackground = NULL;
    mNext = NULL;
    srand(time(NULL));
    mAngle = 0;
    mBullet = NULL;
    mShot = NULL;
    mTanks = NULL;
    mTankGraphics = NULL;
    mTurretGraphics = NULL;

    mFrames = 0;

    temp = new VideoLayer[NUM_STEPS]();

    mDest.x = 0;
    mDest.y = 0;
    mDest.w = 32;
    mDest.h = 32;

    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 32;
    mSrc.h = 32;

    mMoveX = 0;
    mMoveY = 0;

    mMap = new GameMap("map/test.wt2");
}

BuildMapModule::~BuildMapModule()
{
}

bool BuildMapModule::onInit()
{
    //SDL_EnableKeyRepeat(5, 5); //we want key repeating for scrolling

    mShot = GameEngine::loadSound("audio/hyah.wav");

    //mMusic = GameEngine::loadMusic("audio/portal_still_alive.mp3");
    //Mix_PlayMusic(mMusic, -1);

    mTileset = new VideoLayer();
    mTileset->surface = VideoLayer::getImage("images/tileset.png");
    mTileset->priority = PRIORITY_BACKGROUND;

    mFPS = new TextLayer();
    mFPS->setColor(0, 0, 0, 0);
    mFPS->loadFont("images/DejaVuSans.ttf", 12);
    mFPS->setText("0 FPS");
    mFPS->setLocation(600, 500);
    mFPS->priority = PRIORITY_TEXT;



    mTanks = new ActiveTank;
    mTanks->next = NULL;
    mTanks->layer = new VideoLayer();
    mTanks->tank = new Tank(0, 0, mTanks->layer);
    mTanks->layer->priority = PRIORITY_DEFAULT;
    mTanks->layer->location.x = 400;
    mTanks->layer->location.y = 300;

    mTankGraphics = new RotatedGraphic("images/tank_bodies/tank_body.png", NUM_STEPS);
    mTurretGraphics = new RotatedGraphic("images/turrets/turret0.png", NUM_STEPS);

    mTanks->layer->surface = mTanks->tank->getTank(mTankGraphics, mTurretGraphics);

    mSrc.x = 0;
    mSrc.y = 0;


    // The following setup code is placed here only for development purposes
    // In final release, it should be in the onLoop() function, and a different
    // Module should be used to display the map
    mBackground = new VideoLayer();

    mBackground->surface = mMap->getSurface();
    mBackground->setLocation(0, 0);
    mBackground->priority = PRIORITY_BACKGROUND;

    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 800;
    mSrc.h = 600;

    mDest.x = 40;
    mDest.y = 30;

    // End of development code

    mMouse = new VideoLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    GameEngine::addLayer(mTanks->layer);
    GameEngine::addLayer(mFPS);
    GameEngine::addLayer(mMouse);

    mNext = new TestModule();

    mNextSecond = SDL_GetTicks() + 1000;
    return true;
}

void BuildMapModule::onLoop()
{
    mFrames++;
//    mSrc.x += mMoveX;
//    mSrc.y += mMoveY;
//
//    if (mSrc.x > 0)
//    {
//        mSrc.x = 0;
//    }
//    else if (mSrc.x < (800 - X))
//    {
//        mSrc.x = 800 - X;
//    }
//
//    if (mSrc.y > 0)
//    {
//        mSrc.y = 0;
//    }
//    else if (mSrc.y < (600 - Y))
//    {
//        mSrc.y = 600 - Y;
//    }
//
//    //SDL_BlitSurface(picSurface, &mSrc, mBackground->surface, NULL);
//    //mBackground->setLocation(mSrc.x, mSrc.y);
//    SDL_Rect* r = GameEngine::moveCamera(mMoveX, mMoveY);
//
//    mSrc.x = r->x;
//    mSrc.y = r->y;
//
//    SDL_Rect* r = NULL;
//
//
//    SDL_Delay(5);
}

void BuildMapModule::onFrame()
{
    if (mBullet != NULL)
    {
        mBullet->onUpdate();
    }

    if (mMoveX || mMoveY)
    {
        GameEngine::moveCamera(mMoveX, mMoveY);
    }

    if (SDL_GetTicks() > mNextSecond)
    {
        static stringstream s;
        s << mFrames << " FPS";
        mFPS->setText(s.str().c_str());
        mNextSecond = SDL_GetTicks() + 1000;
        mFrames = 0;
        s.str("");
    }

    ActiveTank* iterator = mTanks;

    //first update this players tank so we can set the camera correctly
    iterator->tank->updateTank(mMap);
    iterator->layer->surface = iterator->tank->getTank(mTankGraphics, mTurretGraphics);
    GameEngine::setCamera(mTanks->layer->location.x + 16 - 400, mTanks->layer->location.y + 16 - 300);
    iterator = iterator->next;

    //now update everyone elses tanks
    while (iterator != NULL)
    {
        iterator->tank->updateTank(mMap);
        iterator->layer->surface = mTanks->tank->getTank(mTankGraphics, mTurretGraphics);
        iterator = iterator->next;
    }
    //GameEngine::buildSurfaces();
}

void BuildMapModule::onCleanup()
{
    SDL_FreeSurface(mBackground->surface);
    SDL_FreeSurface(mMouse->surface);

    GameEngine::freeSound(mShot);

    for (int i = 0; i < NUM_STEPS; i++)
    {
        SDL_FreeSurface(temp[i].surface);
    }
    delete [] temp;
    delete mBackground;
    delete mMouse;
}

EngineModule* BuildMapModule::getNextModule()
{
    return mNext;
    //return NULL;
}

void BuildMapModule::onMouseMove(int inX, int inY, int inRelX, int inRelY,
    bool inLeft, bool inRight, bool inMiddle)
{
    int turretX = mTanks->layer->location.x + 16;
    int turretY = mTanks->layer->location.y + 16;

    int which = 0;
    if (mMouse == NULL) return;
    mMouse->setLocation(inX, inY);


    SDL_Rect* r = GameEngine::getCamera();

    double x = (double)((inX + r->x) - turretX);
    double y = (double)((inY + r->y) - turretY);
    r = NULL;
    double angle = atan2(y, x) * 180 / 3.14159265;
    if (angle < 0)
    {
        angle += 360;
    }
    mAngle = angle;


    which = (int(angle / (360 / NUM_STEPS)));

    mTanks->tank->setTurret(which);
    mTanks->layer->surface = mTanks->tank->getTank(mTankGraphics, mTurretGraphics); //temp[which].surface;

}

void BuildMapModule::onLButtonDown(int inX, int inY)
{
    GameEngine::playSound(mShot);
    if (mBullet != NULL)
    {
        GameEngine::removeLayer(mBullet->getLayer());
        SDL_FreeSurface(mBullet->getLayer()->surface);
        delete mBullet;
    }

    SDL_Rect* r = GameEngine::getCamera();

    double turretX = (double)mTanks->layer->location.x;
    double turretY = (double)mTanks->layer->location.y;
    mBullet = new Bullet((double)((inX + r->x) - turretX), (double)((inY + r->y) - turretY), turretX + 0.0, turretY + 0.0, 10.0);
    GameEngine::addLayer(mBullet->getLayer());

}

void BuildMapModule::onRButtonDown(int inX, int inY)
{
    GameEngine::onExit();

}

void BuildMapModule::onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue)
{
//    if ((abs((int)inValue) <= (32767 * .05)) && ((int)inAxis == 0 || (int)inAxis == 1))
//    {
//        mTanks->tank->moveTankX(0);
//        mTanks->tank->moveTankY(0);
//    }

    int a = (int)inAxis;

    int v = (int)inValue;

    if (abs(v) <= 2000)
    {
        v = 0;
    }
    switch(a)
    {
        case 0:
        {
            mTanks->tank->moveTankX(v);
            break;
        }
        case 1:
        {
            mTanks->tank->moveTankY(v);
            break;
        }
    }

}

void BuildMapModule::onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    int c = inSym; //what key is this
    int amount = 0; //number of pixels to increment/decrement by

    if (c == SDLK_LEFT)
    {
        mMoveX = -amount;
        mTanks->tank->moveTankX(-500);
    }
    if (c == SDLK_RIGHT)
    {
        mMoveX = amount;
        mTanks->tank->moveTankX(500);
    }
    if (c == SDLK_UP)
    {
        mMoveY = -amount;
        mTanks->tank->moveTankY(-500);

    }
    if (c == SDLK_DOWN)
    {
        mMoveY = amount;
        mTanks->tank->moveTankY(500);
    }

    //mTanks->layer->setLocation(400 - (mTanks->layer->surface->w / 2), 300 - (mTanks->layer->surface->h / 2));

}

void BuildMapModule::onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    int c = inSym; //what key is this

    if (c == SDLK_LEFT)
    {
        mMoveX = 0;
        mTanks->tank->moveTankX(0);
    }
    if (c == SDLK_RIGHT)
    {
        mMoveX = 0;
        mTanks->tank->moveTankX(0);
    }
    if (c == SDLK_UP)
    {
        mMoveY = 0;
        mTanks->tank->moveTankY(0);
    }
    if (c == SDLK_DOWN)
    {
        mMoveY = 0;
        mTanks->tank->moveTankY(0);
    }
}

SDL_Surface* BuildMapModule::getCanvas()
{
    return mBackground->surface;
}
