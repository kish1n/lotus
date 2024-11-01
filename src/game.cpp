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
    m_window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_window == NULL)
    {
        fatal("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(m_window);

    // Fill the surface white
    SDL_FillSurfaceRect(screenSurface, nullptr, SDL_MapSurfaceRGB(screenSurface, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(m_window);

    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }
    }
}

Game::~Game()
{
    // Destroy window
    SDL_DestroyWindow(m_window);

    // Quit SDL subsystems
    SDL_Quit();
}