#pragma once

#include "raylib.h"

#include "GameState.h"
#include "entities/Player.h"
#include "world/World.h"

class Game
{
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Run();

private:
    static constexpr int SCREEN_WIDTH = 1280;
    static constexpr int SCREEN_HEIGHT = 720;

    Player player_;
    World world_;
    Camera2D camera_;
    GameState state_;
    bool initialized_;
    bool shouldClose_;

    void Initialize();
    void Update(float deltaTime);
    void Draw() const;

    void UpdateMainMenu();
    void UpdatePlaying(float deltaTime);
    void UpdatePaused();
    void UpdateExitConfirmation();
};
