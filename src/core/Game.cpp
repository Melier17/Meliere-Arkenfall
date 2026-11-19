#include "Game.h"

Game::Game()
    : camera_{},
      initialized_(false)
{
}

Game::~Game()
{
    if (initialized_)
    {
        CloseWindow();
    }
}

void Game::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MELIERE - ARKENFALL");
    SetTargetFPS(60);

    camera_ = {};
    camera_.offset = {
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f
    };
    camera_.target = player_.GetCenter();
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;

    initialized_ = true;
}

void Game::Update(float deltaTime)
{
    player_.Update(deltaTime, world_);
    camera_.target = player_.GetCenter();
}

void Game::Draw() const
{
    BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera_);
            world_.Draw();
            player_.Draw();
        EndMode2D();

        DrawRectangle(12, 12, 390, 72, Fade(BLACK, 0.65f));
        DrawText("ARKENFALL - PROTOTYPE v0.1.0", 24, 22, 20, GOLD);
        DrawText("Move: WASD / Arrow keys", 24, 50, 16, RAYWHITE);
        DrawFPS(SCREEN_WIDTH - 90, 16);
    EndDrawing();
}

void Game::Run()
{
    Initialize();

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        Update(deltaTime);
        Draw();
    }
}
