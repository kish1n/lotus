#include "lotus/Game.h"
#include "lotus/BallObject.h"
#include "lotus/ResourceManager.h"
#include "lotus/SpriteRenderer.h"

#include <SDL3/SDL_scancode.h>
#include <chrono>

SpriteRenderer *Renderer = nullptr;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);

GameObject *Player;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

BallObject *Ball;

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
    ResourceManager::LoadTexture("Content/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("Content/textures/block.png", false, "block");
    ResourceManager::LoadTexture("Content/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("Content/textures/paddle.png", true, "paddle");
    // load levels
    GameLevel one;
    one.Load("Content/levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two;
    two.Load("Content/levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three;
    three.Load("Content/levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four;
    four.Load("Content/levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    glm::vec2 playerPos =
        glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos =
        playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                          ResourceManager::GetTexture("face"));
}

void Game::Update(float dt) { Ball->Move(dt, this->Width); }

void Game::ProcessInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[SDL_SCANCODE_A]) {
            if (Player->Position.x >= 0.0f) {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[SDL_SCANCODE_D]) {
            if (Player->Position.x <= this->Width - Player->Size.x) {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->Keys[SDL_SCANCODE_SPACE])
            Ball->Stuck = false;
    }
}

void Game::Render() {

    if (this->State == GAME_ACTIVE) {
        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f),
                             glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        Ball->Draw(*Renderer);
        Player->Draw(*Renderer);
    }

    float time =
        std::chrono::duration<float>(std::chrono::steady_clock::now().time_since_epoch()).count();
    float rotation = time * 180.0f; // 30 degrees per second

    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f),
                         glm::vec2(300.0f, 300.0f), rotation, glm::vec3(0.f, 1.0f, 0.f));
}
