#include "GameEngine.h"
#include "BeginModule.h"


int main(int argc, char** argv)
{
    GameEngine ge;

    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);



    return ge.start(new BeginModule()) ? 0 : 1;
}
