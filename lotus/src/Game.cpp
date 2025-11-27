#include "lotus/Game.h"
#include "lotus/ResourceManager.h"
#include "lotus/SpriteRenderer.h"

#include <chrono>

SpriteRenderer *Renderer = nullptr;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game() { delete Renderer; }

void Game::Init() {
    // load shaders
    ResourceManager::LoadShader("Content/shaders/sprite.vert", "Content/shaders/sprite.frag",
                                nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("Content/textures/awesomeface.png", true, "face");
}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {}

void Game::Render() {
    float time =
        std::chrono::duration<float>(std::chrono::steady_clock::now().time_since_epoch()).count();

    float rotation = time * 30.0f; // 30 degrees per second

    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f),
                         glm::vec2(300.0f, 400.0f), rotation, glm::vec3(1.0f, 1.0f, 1.0f));
}
