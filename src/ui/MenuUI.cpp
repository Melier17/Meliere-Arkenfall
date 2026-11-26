#include "MenuUI.h"

namespace
{
    constexpr Rectangle START_BUTTON = { 490.0f, 330.0f, 300.0f, 58.0f };
    constexpr Rectangle MENU_EXIT_BUTTON = { 490.0f, 408.0f, 300.0f, 58.0f };
    constexpr Rectangle RESUME_BUTTON = { 490.0f, 300.0f, 300.0f, 54.0f };
    constexpr Rectangle MAIN_MENU_BUTTON = { 490.0f, 370.0f, 300.0f, 54.0f };
    constexpr Rectangle PAUSE_EXIT_BUTTON = { 490.0f, 440.0f, 300.0f, 54.0f };
    constexpr Rectangle CONFIRM_BUTTON = { 390.0f, 390.0f, 220.0f, 54.0f };
    constexpr Rectangle CANCEL_BUTTON = { 670.0f, 390.0f, 220.0f, 54.0f };

    bool IsPressed(Rectangle bounds)
    {
        return CheckCollisionPointRec(GetMousePosition(), bounds)
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
}

namespace MenuUI
{
    Rectangle GetButtonBounds(Button button)
    {
        switch (button)
        {
            case Button::Start: return START_BUTTON;
            case Button::MenuExit: return MENU_EXIT_BUTTON;
            case Button::Resume: return RESUME_BUTTON;
            case Button::MainMenu: return MAIN_MENU_BUTTON;
            case Button::PauseExit: return PAUSE_EXIT_BUTTON;
            case Button::ConfirmExit: return CONFIRM_BUTTON;
            case Button::CancelExit: return CANCEL_BUTTON;
        }
        return {};
    }

    bool IsButtonPressed(Button button)
    {
        return IsPressed(GetButtonBounds(button));
    }

    void DrawButton(Button button, const char* label)
    {
        const Rectangle bounds = GetButtonBounds(button);
        const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
        const Color fill = hovered
            ? Color{ 115, 91, 55, 255 }
            : Color{ 65, 58, 49, 255 };

        DrawRectangleRec(bounds, fill);
        DrawRectangleLinesEx(bounds, 2.0f, GOLD);

        const int textWidth = MeasureText(label, 22);
        DrawText(label,
            static_cast<int>(bounds.x + (bounds.width - textWidth) / 2.0f),
            static_cast<int>(bounds.y + (bounds.height - 22.0f) / 2.0f),
            22, RAYWHITE);
    }

    void DrawScreenTitle(const char* subtitle)
    {
        const char* title = "ARKENFALL";
        const int titleWidth = MeasureText(title, 58);
        DrawText(title, (1280 - titleWidth) / 2, 150, 58, GOLD);

        const int subtitleWidth = MeasureText(subtitle, 20);
        DrawText(subtitle, (1280 - subtitleWidth) / 2, 225, 20, RAYWHITE);
    }

    void DrawMenuBackground()
    {
        ClearBackground(Color{ 24, 34, 32, 255 });
        DrawRectangle(0, 0, 1280, 720, Color{ 29, 43, 39, 255 });

        for (int x = 0; x < 1280; x += 80)
            DrawLine(x, 0, x, 720, Color{ 39, 54, 47, 255 });

        for (int y = 0; y < 720; y += 80)
            DrawLine(0, y, 1280, y, Color{ 39, 54, 47, 255 });
    }
}
