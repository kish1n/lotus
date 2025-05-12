#include "lotus/RenderManager.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "lotus/base.h"
#include "lotus/render.h"

constexpr int STARTING_SCREEN_WIDTH = 640;
constexpr int STARTING_SCREEN_HEIGHT = 480;

RenderManager::RenderManager()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fatal("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    m_window = SDL_CreateWindow("SDL Tutorial", STARTING_SCREEN_WIDTH, STARTING_SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        fatal("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetSwapInterval(0);
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (!glContext)
    {
        fatal("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    if (!SDL_GL_MakeCurrent(m_window, glContext))
    {
        fatal("Failed to make current context! SDL_Error: %s\n", SDL_GetError());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        fatal("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, STARTING_SCREEN_WIDTH, STARTING_SCREEN_HEIGHT);

    m_drawer = std::make_unique<BasicTriangleDrawer>();
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
