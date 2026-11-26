#pragma once

#include "raylib.h"

namespace MenuUI
{
    enum class Button
    {
        Start,
        MenuExit,
        Resume,
        MainMenu,
        PauseExit,
        ConfirmExit,
        CancelExit,
        RacePrevious,
        RaceNext,
        ArchetypeNext,
        CreateCharacter,
        BackToMenu
    };

    Rectangle GetButtonBounds(Button button);
    bool IsButtonPressed(Button button);
    void DrawButton(Button button, const char* label);
    void DrawScreenTitle(const char* subtitle);
    void DrawMenuBackground();
}
