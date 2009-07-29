#include "TestModule.h"
using namespace std;

TestModule::TestModule()
{
    mChannel = -1;
    mMusic = NULL;
    mSound = NULL;
    mMouse = NULL;
    mTest = NULL;
    mFPS = NULL;
    mFrames = 0;
    mJS1 = NULL;
}

TestModule::~TestModule()
{
}

bool TestModule::onInit()
{
    mTest = new StaticLayer();
    mTest->surface = VideoLayer::getImage("images/temple_fog.jpg");
    mTest->priority = PRIORITY_BACKGROUND;

    mMouse = new StaticLayer();
    mMouse->surface = VideoLayer::getImage("images/normal.png");
    mMouse->priority = PRIORITY_MOUSE;
    SDL_ShowCursor(SDL_DISABLE);

    mText = new TextLayer();
    mText->setColor(255, 0, 0, 0);
    mText->loadFont("images/DejaVuSans.ttf", 32);
    mText->setText("MOUSE");
    mText->setLocation(50, 50);
    mText->priority = PRIORITY_TEXT;

    mFPS = new TextLayer();
    mFPS->setColor(128, 128, 128, 0);
    mFPS->loadFont("images/DejaVuSans.ttf", 16);
    mFPS->setText("0 FPS");
    mFPS->setLocation(600, 500);
    mFPS->priority = PRIORITY_TEXT;

    mJS1 = new TextLayer();
    mJS1->setColor(0, 255, 255, 0);
    mJS1->loadFont("images/DejaVuSans.ttf", 32);
    mJS1->setText("JOYSTICK 1");
    mJS1->setLocation(400, 50);
    mJS1->priority = PRIORITY_TEXT;

    mJS2 = new TextLayer();
    mJS2->setColor(0, 255, 255, 0);
    mJS2->loadFont("images/DejaVuSans.ttf", 32);
    mJS2->setText("JOYSTICK 2");
    mJS2->setLocation(400, 100);
    mJS2->priority = PRIORITY_TEXT;

    mJS3 = new TextLayer();
    mJS3->setColor(0, 255, 255, 0);
    mJS3->loadFont("images/DejaVuSans.ttf", 32);
    mJS3->setText("JOYSTICK 3");
    mJS3->setLocation(400, 150);
    mJS3->priority = PRIORITY_TEXT;

    mYoshi = new AnimatedLayer();
    mYoshi->loadSheet("images/yoshi.png", 64, 8);
    mYoshi->priority = PRIORITY_GUI;
    mYoshi->location->x = 100;
    mYoshi->location->y = 100;
    mYoshi->update();

    mEngine->addLayer(mTest);
    mEngine->addLayer(mMouse);
    mEngine->addLayer(mText);
    mEngine->addLayer(mFPS);
    mEngine->addLayer(mJS1);
    mEngine->addLayer(mJS2);
    mEngine->addLayer(mJS3);
    mEngine->addLayer(mYoshi);

    //mMusic = Mix_LoadMUS("theme.ogg");
    //Mix_PlayMusic(mMusic, 0);
    //Mix_HookMusicFinished(onMusicEnd);

    //mSound = Mix_LoadWAV("buzztest.wav");

    mNextSecond = SDL_GetTicks() + 1000;
    mNextFrame += NEXT_FRAME * 3;

    return true;
}

void TestModule::onLoop()
{
    stringstream s;

    mFrames++;

    if (SDL_GetTicks() > mNextFrame)
    {
        mNextFrame += NEXT_FRAME * 3;
        mYoshi->update();
    }

    if (SDL_GetTicks() > mNextSecond)
    {
        s << mFrames << " FPS";
        mFPS->setText(s.str().c_str());
        mNextSecond = SDL_GetTicks() + 1000;
        mFrames = 0;
    }
}

void TestModule::onCleanup()
{
    if (mMusic != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(mMusic);
        mMusic = NULL;
    }

    delete mTest;
    delete mMouse;
    delete mText;
    delete mFPS;
    delete mJS1;
    delete mJS2;
    delete mJS3;
    delete mYoshi;
}

EngineModule* TestModule::getNextModule()
{
    return NULL;
}

void TestModule::onMouseMove(int inX, int inY, int inRelX, int inRelY,
    bool inLeft, bool inRight, bool inMiddle)
{
    std::stringstream s;
    s << inX << " : " << inY;
    mText->setText(s.str().c_str());
    if (mMouse == NULL) return;
    mMouse->setLocation(inX, inY);
}

void TestModule::onLButtonDown(int inX, int inY)
{
    //mChannel = Mix_PlayChannel(-1, mSound, 0);
//    if (mChannel < 0)
//    {
//        mChannel = Mix_PlayChannel(-1, mSound, 0);
//    }
//    else
//    {
//        Mix_HaltChannel(mChannel);
//        mChannel = -1;
//    }
}

void TestModule::onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue)
{
    stringstream s;
    int w = (int) inWhich;
    int a = (int) inAxis;
    int v = (int) inValue;
    //s << "w " << w << " a " << a << " v " << v;
    s << v;
    if (a % 2 == 0)
    {
        mJS1->setText(s.str().c_str());
    }
    else
    {
        mJS2->setText(s.str().c_str());
    }
}

void TestModule::onJoyButtonDown(Uint8 inWhich, Uint8 inButton)
{
    stringstream s;
    int w = (int) inWhich;
    int b = (int) inButton;
    s << "b " << b;
    mJS3->setText(s.str().c_str());
}

void TestModule::onJoyButtonUp(Uint8 inWhich, Uint8 inButton)
{
}

void TestModule::onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue)
{
}

void TestModule::onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
    Sint16 inYRel)
{
}
