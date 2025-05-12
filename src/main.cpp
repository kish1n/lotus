#include "lotus/RenderManager.h"
#include "lotus/GameLoop.h"
#include "lotus/State.h"

#include <cstring>

using namespace std;

int main(int argc, char** args)
{
    GameObject triangle;
    triangle.x = 0.4;
    triangle.y = 0.4;
    triangle.width = 0.2;
    triangle.height = 0.2;

    State state;
    state.objs.emplace_back(&triangle);
    RenderManager renderManager;
    GameLoop gameLoop(&renderManager, &state);

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(args[i], "-w") == 0)
        {
            renderManager.setWireframeMode(true);
        }
    }

    return gameLoop.execute();
}