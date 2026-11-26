#include "Game.h"
#include "ui/MenuUI.h"

Game::Game()
    : camera_{},
      state_(GameState::MainMenu),
      initialized_(false),
      shouldClose_(false)
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
    SetExitKey(KEY_NULL);

    camera_ = {};
    camera_.offset = {
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f
    };
    camera_.target = player_.GetCenter();
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;

    initialized_ = IsWindowReady();
}

void Game::Update(float deltaTime)
{
    switch (state_)
    {
        case GameState::MainMenu:
            UpdateMainMenu();
            break;

        case GameState::Playing:
            UpdatePlaying(deltaTime);
            break;

        case GameState::Paused:
            UpdatePaused();
            break;

        case GameState::ExitConfirmation:
            UpdateExitConfirmation();
            break;
    }
}

void Game::UpdateMainMenu()
{
    if (IsKeyPressed(KEY_ENTER) || MenuUI::IsButtonPressed(MenuUI::Button::Start))
    {
        state_ = GameState::Playing;
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE) || MenuUI::IsButtonPressed(MenuUI::Button::MenuExit))
    {
        state_ = GameState::ExitConfirmation;
    }
}

void Game::UpdatePlaying(float deltaTime)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        state_ = GameState::Paused;
        return;
    }

    player_.Update(deltaTime, world_);
    camera_.target = player_.GetCenter();
}

void Game::UpdatePaused()
{
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_R)
        || MenuUI::IsButtonPressed(MenuUI::Button::Resume))
    {
        state_ = GameState::Playing;
        return;
    }

    if (IsKeyPressed(KEY_M) || MenuUI::IsButtonPressed(MenuUI::Button::MainMenu))
    {
        state_ = GameState::MainMenu;
        return;
    }

    if (IsKeyPressed(KEY_Q) || MenuUI::IsButtonPressed(MenuUI::Button::PauseExit))
    {
        state_ = GameState::ExitConfirmation;
    }
}

void Game::UpdateExitConfirmation()
{
    if (IsKeyPressed(KEY_Y) || MenuUI::IsButtonPressed(MenuUI::Button::ConfirmExit))
    {
        shouldClose_ = true;
        return;
    }

    if (IsKeyPressed(KEY_N) || IsKeyPressed(KEY_ESCAPE)
        || MenuUI::IsButtonPressed(MenuUI::Button::CancelExit))
    {
        state_ = GameState::MainMenu;
    }
}

void Game::Draw() const
{
    if (state_ == GameState::Playing || state_ == GameState::Paused)
    {
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera_);
                world_.Draw();
                player_.Draw();
            EndMode2D();

            DrawRectangle(12, 12, 390, 72, Fade(BLACK, 0.65f));
            DrawText("ARKENFALL - PROTOTYPE v0.1.0", 24, 22, 20, GOLD);
            DrawText("Move: WASD / Arrows | ESC: Pause", 24, 50, 16, RAYWHITE);
            DrawFPS(SCREEN_WIDTH - 90, 16);

            if (state_ == GameState::Paused)
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.72f));
                MenuUI::DrawScreenTitle("GAME PAUSED");
                MenuUI::DrawButton(MenuUI::Button::Resume, "RESUME");
                MenuUI::DrawButton(MenuUI::Button::MainMenu, "MAIN MENU");
                MenuUI::DrawButton(MenuUI::Button::PauseExit, "EXIT GAME");
            }
        EndDrawing();

        return;
    }

    BeginDrawing();
        MenuUI::DrawMenuBackground();

        if (state_ == GameState::MainMenu)
        {
            MenuUI::DrawScreenTitle("YOUR WORLD. YOUR LEGEND.");
            MenuUI::DrawButton(MenuUI::Button::Start, "START GAME");
            MenuUI::DrawButton(MenuUI::Button::MenuExit, "EXIT");
            DrawText("MELIERE GAMES", 24, 680, 16, LIGHTGRAY);
            DrawText("PROTOTYPE v0.1.0", 1070, 680, 16, LIGHTGRAY);
        }
        else if (state_ == GameState::ExitConfirmation)
        {
            MenuUI::DrawScreenTitle("LEAVE ARKENFALL?");
            const char* message = "Are you sure you want to close the game?";
            const int messageWidth = MeasureText(message, 22);
            DrawText(message, (SCREEN_WIDTH - messageWidth) / 2, 300, 22, RAYWHITE);
            MenuUI::DrawButton(MenuUI::Button::ConfirmExit, "YES, EXIT");
            MenuUI::DrawButton(MenuUI::Button::CancelExit, "CANCEL");
        }
    EndDrawing();
}

void Game::Run()
{
    Initialize();

    if (!initialized_)
    {
        return;
    }

    while (!WindowShouldClose() && !shouldClose_)
    {
        const float deltaTime = GetFrameTime();
        Update(deltaTime);
        Draw();
    }
}
