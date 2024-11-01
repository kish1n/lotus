#pragma once

#include "SDL3/SDL.h"
#include "render.h"

#include <memory>

class Game
{
public:
    Game();
    virtual ~Game();

private:
    SDL_Window* m_window = nullptr;
    std::unique_ptr<Drawer> m_drawer;
};