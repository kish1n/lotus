#pragma once

#include "SDL3/SDL.h"

class Game
{
public:
    Game();
    virtual ~Game();

private:
    SDL_Window* m_window = nullptr;
};