#include "GameEngine.h"
#include "TestModule.h"

int main(int argc, char** argv)
{
    GameEngine ge;
    return ge.start(new TestModule()) ? 0 : 1;
}
