#include "GameEngine.h"
#include "BeginModule.h"


int main(int argc, char** argv)
{
    putenv("SDL_VIDEODRIVER=directx");
    GameEngine ge;
    return ge.start(new BeginModule()) ? 0 : 1;
}
