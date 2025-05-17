#include "lotus/RenderManager.h"
#include "lotus/GameLoop.h"
#include "lotus/State.h"

#include <cstring>

using namespace std;

int main(int argc, char** args)
{
    GameObject sq1;
    GameObject sq2(0.1, 0.1);

    State state;
    state.objs.insert(state.objs.end(), {&sq1, &sq2});
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