#pragma once

#include <memory>

struct SDL_Window;
class Drawer;

class RenderManager
{
public:
    RenderManager();
    virtual ~RenderManager();

    void setWireframeMode(bool wireframe);
    void render();

private:
    SDL_Window* m_window = nullptr;
    std::unique_ptr<Drawer> m_drawer = nullptr;
};
