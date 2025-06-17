module;

export module lotus:RenderManager;

import std;
import :render;

class Drawer;
class State;
extern "C++" struct SDL_Window;

export class RenderManager {
  public:
    RenderManager();
    virtual ~RenderManager();

    RenderManager(const RenderManager &) = delete;
    RenderManager &operator=(const RenderManager &) = delete;
    RenderManager(RenderManager &&) = delete;
    RenderManager &operator=(RenderManager &&) = delete;

    void setWireframeMode(bool wireframe);
    void render(State *state);

  private:
    SDL_Window *m_window = nullptr;
    std::unique_ptr<Drawer> m_drawer = nullptr;
};
