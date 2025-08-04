export module lotus:Game;

import std;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game {
  public:
    enum class GameState;
    GameState State;
    std::vector<bool> Keys = std::vector<bool>(128);
    unsigned int Width, Height;
    Game(unsigned int width, unsigned int height);
    ~Game();
    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    // Represents the current state of the game
    enum class GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };
};
