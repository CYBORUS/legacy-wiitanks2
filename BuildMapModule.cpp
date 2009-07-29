#include "BuildMapModule.h"

//included for rand(), should be removed after development
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

#define MAP_SIZE 50




BuildMapModule::BuildMapModule()
{
    mMouse = NULL;
    mTileset = NULL;
    mBackground = NULL;
    mNext = NULL;
    picSurface = NULL;
    tempSurface = NULL;
    srand(time(NULL));

    dest.x = 0;
    dest.y = 0;
    dest.w = 32;
    dest.h = 32;

    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

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



    mTileset = new StaticLayer();
    mTileset->surface = VideoLayer::getImage("images/tileset.png");
    mTileset->priority = PRIORITY_BACKGROUND;

    // The following setup code is placed here only for development purposes
    // In final release, it should be in the onLoop() function, and a different
    // Module should be used to display the map
    mBackground = new StaticLayer();

    tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                1600, 1600,
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
                                1600, 1600,
                                32, rmask, gmask, bmask, amask);

    mBackground->surface = SDL_DisplayFormat(tempSurface);

    SDL_BlitSurface(picSurface, NULL, mBackground->surface, NULL);

    mEngine->addLayer(mBackground);
    // End of development code

    mMouse = new StaticLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    mEngine->addLayer(mMouse);

    mNext = new TestModule();
    return true;
}

void BuildMapModule::onLoop()
{

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
    if (mMouse == NULL) return;
    mMouse->setLocation(inX, inY);
}

void BuildMapModule::onLButtonDown(int inX, int inY)
{
    if (mEngine == NULL) return;
    mEngine->onExit();
}
