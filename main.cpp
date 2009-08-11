#include "GameEngine.h"
#include "BeginModule.h"
#include "BuildMapModule.h"


int main(int argc, char** argv)
{
    putenv("SDL_VIDEODRIVER=directx");
    GameEngine ge;
    return ge.start(new BuildMapModule()) ? 0 : 1;
}
