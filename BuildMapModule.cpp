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

    mTurretDirections = new StaticLayer[16]();

    dest.x = 0;
    dest.y = 0;
    dest.w = 32;
    dest.h = 32;

    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

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
    //SDL_EnableKeyRepeat(5, 5); //we want key repeating for scrolling



    mTileset = new StaticLayer();
    mTileset->surface = VideoLayer::getImage("images/tileset.png");
    mTileset->priority = PRIORITY_BACKGROUND;

    for (int i = 0; i < 16; i++)
    {
        s << "images/turrets/turret" << i << ".png";
        mTurretDirections[i].surface = VideoLayer::getImage(s.str().c_str());
        mTurretDirections[i].setLocation(50, 50);
        mTurretDirections[i].priority = PRIORITY_DEFAULT;
        s.str("");
    }

    mTurret = new StaticLayer();
    mTurret->surface = mTurretDirections[0].surface;
    //SDL_SetColorKey(mTurret->surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(mTurret->surface->format, 0xFF, 0x0, 0xFF));
    mTurret->priority = PRIORITY_DEFAULT;
    mTurret->setLocation(400, 300);

    // The following setup code is placed here only for development purposes
    // In final release, it should be in the onLoop() function, and a different
    // Module should be used to display the map
    mBackground = new StaticLayer();

    tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                X, Y,
                                32, rmask, gmask, bmask, amask);

    picSurface = SDL_DisplayFormat(tempSurface);
    mBackground->priority = PRIORITY_BACKGROUND;
    SDL_FreeSurface(tempSurface);

    for (int i = 0; i < MAP_SIZE; i++)
    {
        dest.y = i * 32;
        for (int j = 0; j < MAP_SIZE; j++)
        {
            src.x = tileMap[i][j] * 32;
            dest.x = j * 32;

            if (SDL_BlitSurface(mTileset->surface, &src, picSurface, &dest) == -2)
            {
                cerr << "blitting failed" << endl;
                exit(4);
            }
        }
    }
    tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                X, Y,
                                32, rmask, gmask, bmask, amask);

    mBackground->surface = SDL_DisplayFormat(tempSurface);
    SDL_FreeSurface(tempSurface);

    src.x = 0;
    src.y = 0;
    src.w = 800;
    src.h = 600;

    dest.x = 40;
    dest.y = 30;

    SDL_BlitSurface(picSurface, &src, mBackground->surface, NULL);

    //SDL_BlitSurface(mTurret->surface, NULL, mBackground->surface, &dest);

    mEngine->addLayer(mBackground);
    // End of development code

    mMouse = new StaticLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    mEngine->addLayer(mTurret);
    mEngine->addLayer(mMouse);

    mNext = new TestModule();
    return true;
}

void BuildMapModule::onLoop()
{
    src.x += xMove;
    src.y += yMove;

    if (src.x < 0)
    {
        src.x = 0;
    }
    else if (src.x > (X - 800))
    {
        src.x = X - 800;
    }

    if (src.y < 0)
    {
        src.y = 0;
    }
    else if (src.y > (Y - 600))
    {
        src.y = Y - 600;
    }

    SDL_BlitSurface(picSurface, &src, mBackground->surface, NULL);

    SDL_Delay(5);
}

void BuildMapModule::onCleanup()
{
    delete mBackground;
    delete mMouse;
}

EngineModule* BuildMapModule::getNextModule()
{
    return mNext;
}

void BuildMapModule::onMouseMove(int inX, int inY, int inRelX, int inRelY, bool inLeft,
            bool inRight, bool inMiddle)
{
    int turretX = mTurret->location->x + 16;
    int turretY = mTurret->location->y + 16;
    int which = 0;
    if (mMouse == NULL) return;
    mMouse->setLocation(inX, inY);

    double x = (double)(inX - turretX);
    double y = (double)(inY - turretY) * -1.0;
    double angle = atan2(y, x) * 180 / 3.14159265;
    if (angle < 0)
    {
        angle += 360;
    }


    which = (int(angle * 2.0 / 45.0 + 1)) % 16;


    mTurret->surface = mTurretDirections[which].surface;
}

void BuildMapModule::onLButtonDown(int inX, int inY)
{
    if (mEngine == NULL) return;
    mEngine->onExit();
}

void BuildMapModule::onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    int c = inSym; //what key is this
    int amount = 5; //number of pixels to increment/decrement by

    if (c == SDLK_LEFT)
    {
        xMove = -amount;
    }
    if (c == SDLK_RIGHT)
    {
        xMove = amount;
    }
    if (c == SDLK_UP)
    {
        yMove = -amount;

    }
    if (c == SDLK_DOWN)
    {
        yMove = amount;
    }
}

void BuildMapModule::onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    int c = inSym; //what key is this

    if (c == SDLK_LEFT)
    {
        xMove = 0;
    }
    if (c == SDLK_RIGHT)
    {
        xMove = 0;
    }
    if (c == SDLK_UP)
    {
        yMove = 0;

    }
    if (c == SDLK_DOWN)
    {
        yMove = 0;
    }
}
