#include "lotus/render.h"

#include "lotus/base.h"

#include "glad/glad.h"


Drawer::Drawer()
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        fatal("Failed to initialize GLAD\n");
    }
}

void Drawer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
}
