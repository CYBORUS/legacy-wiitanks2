#include "GameEngine.h"
#include "BeginModule.h"
#include "Preferences.h"


int main(int argc, char** argv)
{
    GameEngine::start(new BeginModule());
    return 0;
}
