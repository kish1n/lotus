#pragma once

class RenderManager;

class GameLoop
{
public:
    GameLoop(RenderManager* renderManager) : m_renderManager(renderManager) {}
    virtual ~GameLoop() = default;

    int execute();
private:
    RenderManager* m_renderManager = nullptr;
};