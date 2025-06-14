module;
#include "glad/glad.h"
#include "SDL3/SDL.h"

module lotus;

import std;
import :base;
import :render;
import :RenderManager;

constexpr int STARTING_SCREEN_WIDTH = 640;
constexpr int STARTING_SCREEN_HEIGHT = 480;

RenderManager::RenderManager()
{
    std::cout << "RenderManager() - START" << std::endl;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fatal(std::format("SDL could not initialize! SDL_Error: {}", SDL_GetError()));
    }

    m_window = SDL_CreateWindow("SDL Tutorial", STARTING_SCREEN_WIDTH, STARTING_SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        fatal(std::format("Window could not be created! SDL_Error: {}", SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetSwapInterval(0);
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (!glContext)
    {
        fatal(std::format("OpenGL context could not be created! SDL_Error: {}", SDL_GetError()));
    }
    if (!SDL_GL_MakeCurrent(m_window, glContext))
    {
        fatal(std::format("Failed to make current context! SDL_Error: {}", SDL_GetError()));
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        fatal("Failed to initialize GLAD");
    }

    glViewport(0, 0, STARTING_SCREEN_WIDTH, STARTING_SCREEN_HEIGHT);

    m_drawer = std::make_unique<BasicTriangleDrawer>();

    std::cout << "RenderManager() - END" << std::endl;
}

void RenderManager::render(State* state)
{
    m_drawer->draw(state);
    SDL_GL_SwapWindow(m_window);
}

void RenderManager::setWireframeMode(bool wireframe)
{
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

RenderManager::~RenderManager()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
