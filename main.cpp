#include "GameEngine.h"
#include "BeginModule.h"


int main(int argc, char** argv)
{
    GameEngine ge;





    return ge.start(new BeginModule()) ? 0 : 1;
}
