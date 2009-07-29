#include "BuildMapModule.h"
using namespace std;



BuildMapModule::BuildMapModule()
{
    mMouse = NULL;
    mBackground = NULL;
    mNext = NULL;
    picSurface = NULL;
    tempSurface = NULL;

    dest.x = 0;
    dest.y = 0;
}

BuildMapModule::~BuildMapModule()
{
}

bool BuildMapModule::onInit()
{
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
}
