#include "lotus/game.h"
#include "lotus/base.h"
#include "glm/vec3.hpp"
#include "glad/glad.h"

using namespace std;

int main(int argc, char** args)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(args[i], "-w") == 0)
        {
            CONFIG::WIREFRAME_MODE = true;
        }
    }

    Game g;

    return 0;
}