/*#include "lotus/RenderManager.h"
#include "lotus/GameLoop.h"
#include "lotus/State.h"*/

import std;
import lotus;

using namespace std;

void timeout(int seconds);

int main(int argc, char** args)
{
    std::cout << "Starting Lotus Game Engine Testing Playground..." << std::endl;
    auto fut = std::async(std::launch::async, timeout, 5);

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

void timeout(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::cerr << "Timeout reached. Terminating program.\n";
    std::exit(0);
}