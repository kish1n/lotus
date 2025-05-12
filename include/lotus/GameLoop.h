#pragma once

class RenderManager;
class State;

class GameLoop
{
public:
    GameLoop(RenderManager* renderManager, State* state) : m_renderManager(renderManager), m_state(state) {}
    virtual ~GameLoop() = default;

    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;
    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;

    int execute();
private:
    RenderManager* m_renderManager = nullptr;
    State* m_state = nullptr;
};