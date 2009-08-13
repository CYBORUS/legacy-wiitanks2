#include "BuildMapModule.h"

//included for rand(), should be removed after development
#include <cstdlib>
#include <iostream>
using namespace std;



int X = MAP_SIZE * 32;
int Y = MAP_SIZE * 32;


BuildMapModule::BuildMapModule()
{
    mMouse = NULL;
    mTileset = NULL;
    mBackground = NULL;
    mNext = NULL;
    picSurface = NULL;
    tempSurface = NULL;
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

    tempRect = new SDL_Rect();
    tempRect->x = 0;
    tempRect->y = 0;
    tempRect->w = 32;
    tempRect->h = 32;

    xMove = 0;
    yMove = 0;

    //create a random dummy map, in actual game we would create
    // a real map

    //first make it all green
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            tileMap[i][j] = 0;
        }
    }

    //then set different colored vertical lines down periodically
    int color = 2;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 10; j < MAP_SIZE; j += 10)
        {
            tileMap[i][j] = color;
                color = (color + 1) % 5;
            if (color < 2)
            {
                color = 2;
            }
        }
        color = 2;

    }

    //then set blue horizontal lines through it periodically
    for (int i = 10; i < MAP_SIZE; i += 10)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            tileMap[i][j] = 1;
        }
    }

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

BuildMapModule::~BuildMapModule()
{
}

bool BuildMapModule::onInit()
{
    SDL_EnableKeyRepeat(5, 5); //we want key repeating for scrolling

    mShot = mEngine->loadSound("audio/hyah.wav");

    //mMusic = mEngine->loadMusic("audio/portal_still_alive.mp3");
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

    tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF,
                                X, Y,
                                32, rmask, gmask, bmask, amask);

    mBackground->surface = SDL_DisplayFormat(tempSurface);
    mBackground->setLocation(0, 0);
    mBackground->priority = PRIORITY_BACKGROUND;
    SDL_FreeSurface(tempSurface);

    for (int i = 0; i < MAP_SIZE; i++)
    {
        mDest.y = i * 32;
        for (int j = 0; j < MAP_SIZE; j++)
        {
            mSrc.x = tileMap[i][j] * 32;
            mDest.x = j * 32;

            if (SDL_BlitSurface(mTileset->surface, &mSrc, mBackground->surface, &mDest) == -2)
            {
                cerr << "blitting failed" << endl;
                exit(4);
            }
        }
    }


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

    mEngine->addLayer(mTanks->layer);
    mEngine->addLayer(mFPS);
    mEngine->addLayer(mMouse);

    mNext = new TestModule();

    mNextSecond = SDL_GetTicks() + 1000;
    return true;
}

void BuildMapModule::onLoop()
{
    mFrames++;
//    mSrc.x += xMove;
//    mSrc.y += yMove;
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
//    tempRect = mEngine->moveCamera(xMove, yMove);
//
//    mSrc.x = tempRect->x;
//    mSrc.y = tempRect->y;
//
//    tempRect = NULL;
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

    if (xMove || yMove)
    {
        mEngine->moveCamera(xMove, yMove);
    }

    if (SDL_GetTicks() > mNextSecond)
    {
        s << mFrames << " FPS";
        mFPS->setText(s.str().c_str());
        mNextSecond = SDL_GetTicks() + 1000;
        mFrames = 0;
        s.str("");
    }

    ActiveTank* iterator = mTanks;

    //first update this players tank so we can set the camera correctly
    iterator->tank->updateTank();
    iterator->layer->surface = iterator->tank->getTank(mTankGraphics, mTurretGraphics);
    mEngine->setCamera(mTanks->layer->location.x + 16 - 400, mTanks->layer->location.y + 16 - 300);
    iterator = iterator->next;

    //now update everyone elses tanks
    while (iterator != NULL)
    {
        iterator->tank->updateTank();
        iterator->layer->surface = mTanks->tank->getTank(mTankGraphics, mTurretGraphics);
        iterator = iterator->next;
    }
    //mEngine->buildSurfaces();
}

void BuildMapModule::onCleanup()
{
    SDL_FreeSurface(mBackground->surface);
    SDL_FreeSurface(mMouse->surface);

    mEngine->freeSound(mShot);

    SDL_FreeSurface(picSurface);

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


    tempRect = mEngine->getCamera();

    double x = (double)((inX + tempRect->x) - turretX);
    double y = (double)((inY + tempRect->y) - turretY);
    tempRect = NULL;
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
    mEngine->playSound(mShot);
    if (mBullet != NULL)
    {
        mEngine->removeLayer(mBullet->getLayer());
        SDL_FreeSurface(mBullet->getLayer()->surface);
        delete mBullet;
    }

    tempRect = mEngine->getCamera();

    double turretX = (double)mTanks->layer->location.x;
    double turretY = (double)mTanks->layer->location.y;
    mBullet = new Bullet((double)((inX + tempRect->x) - turretX), (double)((inY + tempRect->y) - turretY), turretX + 0.0, turretY + 0.0, 10.0);
    mEngine->addLayer(mBullet->getLayer());

}

void BuildMapModule::onRButtonDown(int inX, int inY)
{
    if (mEngine == NULL) return;
    mEngine->onExit();

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
        xMove = -amount;
        mTanks->tank->moveTankX(-500);
    }
    if (c == SDLK_RIGHT)
    {
        xMove = amount;
        mTanks->tank->moveTankX(500);
    }
    if (c == SDLK_UP)
    {
        yMove = -amount;
        mTanks->tank->moveTankY(-500);

    }
    if (c == SDLK_DOWN)
    {
        yMove = amount;
        mTanks->tank->moveTankY(500);
    }

    //mTanks->layer->setLocation(400 - (mTanks->layer->surface->w / 2), 300 - (mTanks->layer->surface->h / 2));

}

void BuildMapModule::onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    int c = inSym; //what key is this

    if (c == SDLK_LEFT)
    {
        xMove = 0;
        mTanks->tank->moveTankX(0);
    }
    if (c == SDLK_RIGHT)
    {
        xMove = 0;
        mTanks->tank->moveTankX(0);
    }
    if (c == SDLK_UP)
    {
        yMove = 0;
        mTanks->tank->moveTankY(0);
    }
    if (c == SDLK_DOWN)
    {
        yMove = 0;
        mTanks->tank->moveTankY(0);
    }
}

SDL_Surface* BuildMapModule::getCanvas()
{
    return mBackground->surface;
}
