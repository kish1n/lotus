#include "lotus/render.h"
#include "lotus/base.h"

#include "GL/glew.h"


void render(SDL_Window& window) {
    SDL_GLContext context = SDL_GL_CreateContext(&window);
    if (context == nullptr)
    {
        fatal("SDL_GLContext could not be created! SDL Error: %s", SDL_GetError());
    }
};