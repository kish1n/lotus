#include "lotus/game.h"
#include "lotus/base.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

Game::Game()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fatal("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Create window
    m_window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (m_window == NULL)
    {
        fatal("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(m_window);

    // Fill the surface white
    SDL_FillSurfaceRect(screenSurface, nullptr, SDL_MapSurfaceRGB(screenSurface, 0x0, 0x0, 0x0));

    // Update the surface
    SDL_UpdateWindowSurface(m_window);

    // load opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (glContext == NULL)
    {
        fatal("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_GL_MakeCurrent(m_window, glContext);
    m_drawer = std::make_unique<Drawer>(SCREEN_WIDTH, SCREEN_HEIGHT);


    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
            if (e.type == SDL_EVENT_KEY_DOWN)
            {
                switch (e.key.key)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
            }
        }

        m_drawer->draw();
        SDL_GL_SwapWindow(m_window);
    }
}

Game::~Game()
{
    // Destroy window
    SDL_DestroyWindow(m_window);

    // Quit SDL subsystems
    SDL_Quit();
}