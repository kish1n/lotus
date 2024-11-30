#pragma once

class RenderManager;

class GameLoop
{
public:
    GameLoop(RenderManager* renderManager) : m_renderManager(renderManager) {}
    virtual ~GameLoop() = default;

    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;
    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;

    int execute();
private:
    RenderManager* m_renderManager = nullptr;
};