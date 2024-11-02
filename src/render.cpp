#include "lotus/render.h"
#include "lotus/base.h"
#include "glad/glad.h"


Drawer::Drawer(int width, int height)
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        fatal("Failed to initialize GLAD\n");
    }

    glClearColor(1.f, 1.f, 1.f, 1.f);

    glViewport(0, 0, width, height);

    
}

void Drawer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
