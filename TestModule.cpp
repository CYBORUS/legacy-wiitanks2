#include "TestModule.h"
using namespace std;

TestModule::TestModule()
{
    mNext = NULL;
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
    mTest = new VideoLayer();
    mTest->surface = VideoLayer::getImage("images/temple_fog.jpg");
    mTest->priority = PRIORITY_BACKGROUND;

    mMouse = new VideoLayer();
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
    mJS1->setColor(0, 128, 255, 0);
    mJS1->loadFont("images/DejaVuSans.ttf", 32);
    mJS1->setText("JOYSTICK 1");
    mJS1->setLocation(400, 50);
    mJS1->priority = PRIORITY_TEXT;

    mJS2 = new TextLayer();
    mJS2->setColor(0, 128, 255, 0);
    mJS2->loadFont("images/DejaVuSans.ttf", 32);
    mJS2->setText("JOYSTICK 2");
    mJS2->setLocation(400, 100);
    mJS2->priority = PRIORITY_TEXT;

    mJS3 = new TextLayer();
    mJS3->setColor(0, 128, 255, 0);
    mJS3->loadFont("images/DejaVuSans.ttf", 32);
    mJS3->setText("JOYSTICK 3");
    mJS3->setLocation(400, 150);
    mJS3->priority = PRIORITY_TEXT;

    mJS4 = new TextLayer();
    mJS4->setColor(0, 128, 255, 0);
    mJS4->loadFont("images/DejaVuSans.ttf", 32);
    mJS4->setText("JOYSTICK 4");
    mJS4->setLocation(400, 200);
    mJS4->priority = PRIORITY_TEXT;

    mJS5 = new TextLayer();
    mJS5->setColor(0, 128, 255, 0);
    mJS5->loadFont("images/DejaVuSans.ttf", 32);
    mJS5->setText("JOYSTICK BUTTONS");
    mJS5->setLocation(400, 250);
    mJS5->priority = PRIORITY_TEXT;

    mJS6 = new TextLayer();
    mJS6->setColor(0, 128, 255, 0);
    mJS6->loadFont("images/DejaVuSans.ttf", 32);
    mJS6->setText("JOYSTICK HAT");
    mJS6->setLocation(400, 300);
    mJS6->priority = PRIORITY_TEXT;

    mYoshi = new AnimatedLayer();
    mYoshi->loadSheet("images/yoshi.png", 64, 8);
    mYoshi->priority = PRIORITY_GUI;
    mYoshi->location.x = 100;
    mYoshi->location.y = 100;
    mYoshi->update();

    GameEngine::addLayer(mTest);
    GameEngine::addLayer(mMouse);
    GameEngine::addLayer(mText);
    GameEngine::addLayer(mFPS);
    GameEngine::addLayer(mJS1);
    GameEngine::addLayer(mJS2);
    GameEngine::addLayer(mJS3);
    GameEngine::addLayer(mJS4);
    GameEngine::addLayer(mJS5);
    GameEngine::addLayer(mJS6);
    GameEngine::addLayer(mYoshi);

    //mMusic = Mix_LoadMUS("theme.ogg");
    //Mix_PlayMusic(mMusic, 0);
    //Mix_HookMusicFinished(onMusicEnd);

    //mSound = Mix_LoadWAV("buzztest.wav");

    mNextSecond = SDL_GetTicks() + 1000;
    mNextFrame = SDL_GetTicks() + NEXT_FRAME * 3;

    return true;
}

void TestModule::onLoop()
{
    mFrames++;
}

void TestModule::onFrame()
{
    stringstream s;
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

    SDL_FreeSurface(mTest->surface);
    SDL_FreeSurface(mMouse->surface);
    SDL_FreeSurface(mText->surface);
    SDL_FreeSurface(mFPS->surface);
    SDL_FreeSurface(mJS1->surface);
    SDL_FreeSurface(mJS2->surface);
    SDL_FreeSurface(mJS3->surface);
    SDL_FreeSurface(mJS4->surface);
    SDL_FreeSurface(mJS5->surface);
    SDL_FreeSurface(mJS6->surface);
    SDL_FreeSurface(mYoshi->surface);

    delete mTest;
    delete mMouse;
    delete mText;
    delete mFPS;
    delete mJS1;
    delete mJS2;
    delete mJS3;
    delete mJS4;
    delete mJS5;
    delete mJS6;
    delete mYoshi;
}

EngineModule* TestModule::getNextModule()
{
    return mNext;
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
    GameEngine::onExit();
}

void TestModule::onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue)
{
    stringstream s;
    int a = (int) inAxis;
    int v = (int) inValue;
    //s << "w " << w << " a " << a << " v " << v;
    s << v;

    switch (a % 4)
    {
        case 0:
            mJS1->setText(s.str().c_str());
            break;
        case 1:
            mJS2->setText(s.str().c_str());
            break;
        case 2:
            mJS3->setText(s.str().c_str());
            break;
        default:
            mJS4->setText(s.str().c_str());
    }
//    if (a % 4 == 0)
//    {
//        mJS1->setText(s.str().c_str());
//    }
//    else if (a % 4 == 1)
//    {
//        mJS2->setText(s.str().c_str());
//    }
//    else if (a % 4 == 2)
//    {
//        mJS3->setText(s.str().c_str());
//    }
//    else
//    {
//        mJS4->setText(s.str().c_str());
//    }
}

void TestModule::onJoyButtonDown(Uint8 inWhich, Uint8 inButton)
{
    stringstream s;
    int b = (int) inButton;
    s << "b " << b;
    mJS5->setText(s.str().c_str());
}

void TestModule::onJoyButtonUp(Uint8 inWhich, Uint8 inButton)
{
}

void TestModule::onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue)
{
    stringstream s;
    int a = (int) inHat;
    int v = (int) inValue;

    s << "hat " << v;
    mJS6->setText(s.str().c_str());
}

void TestModule::onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
    Sint16 inYRel)
{
    cerr << "joyball firing" << endl;
}
