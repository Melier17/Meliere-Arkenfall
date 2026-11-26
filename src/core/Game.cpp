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

        case GameState::CharacterCreation:
            UpdateCharacterCreation();
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
        state_ = GameState::CharacterCreation;
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE) || MenuUI::IsButtonPressed(MenuUI::Button::MenuExit))
    {
        state_ = GameState::ExitConfirmation;
    }
}


void Game::UpdateCharacterCreation()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        state_ = GameState::MainMenu;
        characterNameError_ = false;
        return;
    }

    int codepoint = GetCharPressed();
    while (codepoint > 0)
    {
        if (codepoint >= 32 && codepoint <= 126
            && character_.GetName().size() < 20)
        {
            std::string name = character_.GetName();
            name.push_back(static_cast<char>(codepoint));
            character_.SetName(name);
            characterNameError_ = false;
        }
        codepoint = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        std::string name = character_.GetName();
        if (!name.empty())
            name.pop_back();
        character_.SetName(name);
        characterNameError_ = false;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
    {
        int race = static_cast<int>(character_.GetRace());
        race = (race + (IsKeyPressed(KEY_RIGHT) ? 1 : 2)) % 3;
        character_.SetRace(static_cast<CharacterRace>(race));
    }

    if (IsKeyPressed(KEY_TAB))
    {
        int archetype = static_cast<int>(character_.GetArchetype());
        character_.SetArchetype(static_cast<CharacterArchetype>((archetype + 1) % 3));
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (character_.Create())
        {
            characterNameError_ = false;
            state_ = GameState::Playing;
        }
        else
        {
            characterNameError_ = true;
        }
    }
}

void Game::DrawCharacterCreation() const
{
    MenuUI::DrawScreenTitle("CREATE YOUR ADVENTURER");

    DrawText("CHARACTER NAME", 390, 285, 20, GOLD);
    DrawRectangle(390, 315, 500, 52, Color{ 45, 55, 50, 255 });
    DrawRectangleLines(390, 315, 500, 52, GOLD);
    const std::string displayedName = character_.GetName().empty()
        ? "Type a name..." : character_.GetName();
    DrawText(displayedName.c_str(), 410, 330, 22, RAYWHITE);

    const char* raceName = "Human";
    switch (character_.GetRace())
    {
        case CharacterRace::Human: raceName = "Human"; break;
        case CharacterRace::Elf: raceName = "Elf"; break;
        case CharacterRace::Dwarf: raceName = "Dwarf"; break;
    }

    const char* archetypeName = "Adventurer";
    switch (character_.GetArchetype())
    {
        case CharacterArchetype::Adventurer: archetypeName = "Adventurer"; break;
        case CharacterArchetype::Vanguard: archetypeName = "Vanguard"; break;
        case CharacterArchetype::Arcanist: archetypeName = "Arcanist"; break;
    }

    DrawText("RACE  [LEFT / RIGHT]", 390, 395, 18, LIGHTGRAY);
    DrawText(raceName, 650, 395, 22, GOLD);
    DrawText("ARCHETYPE  [TAB]", 390, 445, 18, LIGHTGRAY);
    DrawText(archetypeName, 650, 445, 22, GOLD);
    DrawText("ENTER: CREATE   |   ESC: BACK", 390, 520, 18, RAYWHITE);

    if (characterNameError_)
        DrawText("Please enter a character name first.", 390, 565, 18, RED);

    DrawText("Prototype choices — final races and archetypes are pending design.",
        250, 650, 16, LIGHTGRAY);
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
    if (state_ == GameState::CharacterCreation)
    {
        BeginDrawing();
            MenuUI::DrawMenuBackground();
            DrawCharacterCreation();
        EndDrawing();
        return;
    }

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
            if (character_.IsCreated())
                DrawText(TextFormat("Character: %s | Lv. %d", character_.GetName().c_str(), character_.GetLevel()), 24, 90, 18, RAYWHITE);
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
