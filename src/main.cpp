#include "lotus/RenderManager.h"
#include "lotus/GameLoop.h"

#include <cstring>

using namespace std;

int main(int argc, char** args)
{

    RenderManager renderManager;
    GameLoop gameLoop(&renderManager);

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(args[i], "-w") == 0)
        {
            renderManager.setWireframeMode(true);
        }
    }

    return gameLoop.execute();
}