#include "lotus/game.h"
#include "lotus/base.h"

#include <chrono>
#include <algorithm>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

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

    // load opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetSwapInterval(0);
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (glContext == NULL)
    {
        fatal("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    if (!SDL_GL_MakeCurrent(m_window, glContext))
    {
        fatal("Failed to make current context! SDL_Error: %s\n", SDL_GetError());
    }

    m_drawer = std::make_unique<BasicTriangleDrawer>();

    SDL_Event e;
    bool running = true;

    std::vector<double> res;

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

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        m_drawer->draw();
        SDL_GL_SwapWindow(m_window);
        
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeSpan = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
        double fps = 1000.0 / timeSpan.count();
        res.push_back(fps);
    }
    std::sort(res.begin(), res.end());
    SDL_Log("Median FPS: %f", res[res.size() / 2]);
}

Game::~Game()
{
    // Destroy window
    SDL_DestroyWindow(m_window);

    // Quit SDL subsystems
    SDL_Quit();
}