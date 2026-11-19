#include "Game.h"

namespace
{
    const Rectangle START_BUTTON = { 490.0f, 330.0f, 300.0f, 58.0f };
    const Rectangle MENU_EXIT_BUTTON = { 490.0f, 408.0f, 300.0f, 58.0f };

    const Rectangle RESUME_BUTTON = { 490.0f, 300.0f, 300.0f, 54.0f };
    const Rectangle MAIN_MENU_BUTTON = { 490.0f, 370.0f, 300.0f, 54.0f };
    const Rectangle PAUSE_EXIT_BUTTON = { 490.0f, 440.0f, 300.0f, 54.0f };

    const Rectangle CONFIRM_BUTTON = { 390.0f, 390.0f, 220.0f, 54.0f };
    const Rectangle CANCEL_BUTTON = { 670.0f, 390.0f, 220.0f, 54.0f };

    bool IsButtonPressed(Rectangle bounds)
    {
        return CheckCollisionPointRec(GetMousePosition(), bounds)
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }

    void DrawButton(Rectangle bounds, const char* label)
    {
        const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
        const Color fill = hovered
            ? Color{ 115, 91, 55, 255 }
            : Color{ 65, 58, 49, 255 };

        DrawRectangleRec(bounds, fill);
        DrawRectangleLinesEx(bounds, 2.0f, GOLD);

        const int textWidth = MeasureText(label, 22);
        DrawText(
            label,
            static_cast<int>(bounds.x + (bounds.width - textWidth) / 2.0f),
            static_cast<int>(bounds.y + (bounds.height - 22.0f) / 2.0f),
            22,
            RAYWHITE
        );
    }

    void DrawScreenTitle(const char* subtitle)
    {
        const char* title = "ARKENFALL";
        const int titleWidth = MeasureText(title, 58);

        DrawText(
            title,
            (1280 - titleWidth) / 2,
            150,
            58,
            GOLD
        );

        const int subtitleWidth = MeasureText(subtitle, 20);
        DrawText(
            subtitle,
            (1280 - subtitleWidth) / 2,
            225,
            20,
            RAYWHITE
        );
    }

    void DrawMenuBackground()
    {
        ClearBackground(Color{ 24, 34, 32, 255 });
        DrawRectangle(0, 0, 1280, 720, Color{ 29, 43, 39, 255 });

        for (int x = 0; x < 1280; x += 80)
        {
            DrawLine(x, 0, x, 720, Color{ 39, 54, 47, 255 });
        }

        for (int y = 0; y < 720; y += 80)
        {
            DrawLine(0, y, 1280, y, Color{ 39, 54, 47, 255 });
        }
    }
}

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
    if (IsKeyPressed(KEY_ENTER) || IsButtonPressed(START_BUTTON))
    {
        state_ = GameState::Playing;
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE) || IsButtonPressed(MENU_EXIT_BUTTON))
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
        || IsButtonPressed(RESUME_BUTTON))
    {
        state_ = GameState::Playing;
        return;
    }

    if (IsKeyPressed(KEY_M) || IsButtonPressed(MAIN_MENU_BUTTON))
    {
        state_ = GameState::MainMenu;
        return;
    }

    if (IsKeyPressed(KEY_Q) || IsButtonPressed(PAUSE_EXIT_BUTTON))
    {
        state_ = GameState::ExitConfirmation;
    }
}

void Game::UpdateExitConfirmation()
{
    if (IsKeyPressed(KEY_Y) || IsButtonPressed(CONFIRM_BUTTON))
    {
        shouldClose_ = true;
        return;
    }

    if (IsKeyPressed(KEY_N) || IsKeyPressed(KEY_ESCAPE)
        || IsButtonPressed(CANCEL_BUTTON))
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
                DrawScreenTitle("GAME PAUSED");
                DrawButton(RESUME_BUTTON, "RESUME");
                DrawButton(MAIN_MENU_BUTTON, "MAIN MENU");
                DrawButton(PAUSE_EXIT_BUTTON, "EXIT GAME");
            }
        EndDrawing();

        return;
    }

    BeginDrawing();
        DrawMenuBackground();

        if (state_ == GameState::MainMenu)
        {
            DrawScreenTitle("YOUR WORLD. YOUR LEGEND.");
            DrawButton(START_BUTTON, "START GAME");
            DrawButton(MENU_EXIT_BUTTON, "EXIT");
            DrawText("MELIERE GAMES", 24, 680, 16, LIGHTGRAY);
            DrawText("PROTOTYPE v0.1.0", 1070, 680, 16, LIGHTGRAY);
        }
        else if (state_ == GameState::ExitConfirmation)
        {
            DrawScreenTitle("LEAVE ARKENFALL?");
            const char* message = "Are you sure you want to close the game?";
            const int messageWidth = MeasureText(message, 22);
            DrawText(message, (SCREEN_WIDTH - messageWidth) / 2, 300, 22, RAYWHITE);
            DrawButton(CONFIRM_BUTTON, "YES, EXIT");
            DrawButton(CANCEL_BUTTON, "CANCEL");
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
