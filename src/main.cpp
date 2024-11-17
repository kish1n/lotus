#include "lotus/game.h"
#include "glm/vec3.hpp"
#include "glad/glad.h"

using namespace std;

bool WIREFRAME_MODE = false;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main(int argc, char** args)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(args[i], "-w") == 0)
        {
            WIREFRAME_MODE = true;
        }
    }

    Game g;

    return 0;
}