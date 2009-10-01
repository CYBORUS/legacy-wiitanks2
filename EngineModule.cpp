#include "EngineModule.h"

EngineModule::EngineModule()
{
}

EngineModule::~EngineModule()
{
}

void EngineModule::onEvent(SDL_Event* inEvent)
{
    switch (inEvent->type)
    {
        case SDL_ACTIVEEVENT:
        {
            switch (inEvent->active.state)
            {
                case SDL_APPMOUSEFOCUS:
                {
                    if (inEvent->active.gain) onMouseFocus();
                    else onMouseBlur();

                    break;
                }
                case SDL_APPINPUTFOCUS:
                {
                    if (inEvent->active.gain) onInputFocus();
                    else onInputBlur();

                    break;
                }
                case SDL_APPACTIVE:
                {
                    if (inEvent->active.gain) onRestore();
                    else onMinimize();

                    break;
                }
            }
            break;
        }

        case SDL_KEYDOWN:
        {
            onKeyDown(inEvent->key.keysym.sym, inEvent->key.keysym.mod,
                inEvent->key.keysym.unicode);
            break;
        }

        case SDL_KEYUP:
        {
            onKeyUp(inEvent->key.keysym.sym, inEvent->key.keysym.mod,
                inEvent->key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            onMouseMove(inEvent->motion.x, inEvent->motion.y,
                inEvent->motion.xrel, inEvent->motion.yrel, (inEvent->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (inEvent->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (inEvent->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            switch (inEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    onLButtonDown(inEvent->button.x, inEvent->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    onRButtonDown(inEvent->button.x, inEvent->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    onMButtonDown(inEvent->button.x, inEvent->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            switch (inEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    onLButtonUp(inEvent->button.x, inEvent->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    onRButtonUp(inEvent->button.x, inEvent->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    onMButtonUp(inEvent->button.x, inEvent->button.y);
                    break;
                }
                case SDL_BUTTON_WHEELUP:
                {
                    onMouseWheel(true, false);
                    break;
                }
                case SDL_BUTTON_WHEELDOWN:
                {
                    onMouseWheel(false, true);
                    break;
                }
            }
            break;
        }

        case SDL_JOYAXISMOTION:
        {
            onJoyAxis(inEvent->jaxis.which, inEvent->jaxis.axis,
                inEvent->jaxis.value);
            break;
        }

        case SDL_JOYBALLMOTION:
        {
            onJoyBall(inEvent->jball.which, inEvent->jball.ball,
                inEvent->jball.xrel, inEvent->jball.yrel);
            break;
        }

        case SDL_JOYHATMOTION:
        {
            onJoyHat(inEvent->jhat.which, inEvent->jhat.hat,
                inEvent->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN:
        {
            onJoyButtonDown(inEvent->jbutton.which, inEvent->jbutton.button);
            break;
        }

        case SDL_JOYBUTTONUP:
        {
            onJoyButtonUp(inEvent->jbutton.which, inEvent->jbutton.button);
            break;
        }

        case SDL_QUIT:
        {
            onExit();
            break;
        }

        case SDL_SYSWMEVENT:
        {
            //Ignore
            break;
        }

        case SDL_VIDEORESIZE:
        {
            onResize(inEvent->resize.w, inEvent->resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE:
        {
            onExpose();
            break;
        }

        default:
        {
            onUser(inEvent->user.type, inEvent->user.code, inEvent->user.data1,
                inEvent->user.data2);
            break;
        }
    }
}

void EngineModule::onInputFocus()
{
}

void EngineModule::onInputBlur()
{
}

void EngineModule::onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
}

void EngineModule::onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
}

void EngineModule::onMouseFocus()
{
}

void EngineModule::onMouseBlur()
{
}

void EngineModule::onMouseMove(int inX, int inY, int inRelX, int inRelY,
    bool inLeft, bool inRight, bool inMiddle)
{
}

void EngineModule::onMouseWheel(bool inUp, bool inDown)
{
}

void EngineModule::onLButtonDown(int inX, int inY)
{
}

void EngineModule::onLButtonUp(int inX, int inY)
{
}

void EngineModule::onRButtonDown(int inX, int inY)
{
}

void EngineModule::onRButtonUp(int inX, int inY)
{
}

void EngineModule::onMButtonDown(int inX, int inY)
{
}

void EngineModule::onMButtonUp(int inX, int inY)
{
}

void EngineModule::onJoyAxis(Uint8 inWhich, Uint8 inAxis, Sint16 inValue)
{
}

void EngineModule::onJoyButtonDown(Uint8 inWhich, Uint8 inButton)
{
}

void EngineModule::onJoyButtonUp(Uint8 inWhich, Uint8 inButton)
{
}

void EngineModule::onJoyHat(Uint8 inWhich, Uint8 inHat, Uint8 inValue)
{
}

void EngineModule::onJoyBall(Uint8 inWhich, Uint8 inBall, Sint16 inXRel,
    Sint16 inYRel)
{
}

void EngineModule::onMinimize()
{
    GameEngine::onMinimize();
}

void EngineModule::onRestore()
{
    GameEngine::onRestore();
}

void EngineModule::onResize(int inWidth, int inHeight)
{
    GameEngine::onResize(inWidth, inHeight);
}

void EngineModule::onExpose()
{
    GameEngine::onExpose();
}

void EngineModule::onExit()
{
    GameEngine::onExit();
}

void EngineModule::onUser(Uint8 inType, int inCode, void* inData1, void* inData2)
{
}

void EngineModule::onFrame()
{
}

void EngineModule::onLoop()
{
}

Surface EngineModule::getCanvas()
{
    Surface t = SDL_CreateRGBSurface(SDL_HWSURFACE, 1000, 1000, 32, GameEngine::mask.red,
        GameEngine::mask.green, GameEngine::mask.blue, GameEngine::mask.alpha);
    Surface u = SDL_DisplayFormat(t);
    SDL_FreeSurface(t);
    return u;
}
