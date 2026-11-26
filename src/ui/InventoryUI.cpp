#include "InventoryUI.h"

#include <algorithm>
#include <string>

namespace
{
    bool inventoryOpen = false;
    int selectedItem = 0;

    constexpr int PANEL_X = 245;
    constexpr int PANEL_Y = 92;
    constexpr int PANEL_WIDTH = 790;
    constexpr int PANEL_HEIGHT = 536;
    constexpr int GRID_X = 280;
    constexpr int GRID_Y = 190;
    constexpr int SLOT_SIZE = 76;
    constexpr int SLOT_GAP = 10;
    constexpr int GRID_COLUMNS = 5;
    constexpr int GRID_ROWS = 4;
}

namespace InventoryUI
{
    void Toggle()
    {
        inventoryOpen = !inventoryOpen;
        if (!inventoryOpen)
            selectedItem = 0;
    }

    void Close()
    {
        inventoryOpen = false;
        selectedItem = 0;
    }

    bool IsOpen()
    {
        return inventoryOpen;
    }

    void Update(const Inventory& inventory)
    {
        if (!inventoryOpen)
            return;

        const int itemCount = static_cast<int>(inventory.GetItems().size());
        const int visibleSlots = GRID_COLUMNS * GRID_ROWS;

        if (itemCount == 0)
            selectedItem = 0;
        else
            selectedItem = std::clamp(selectedItem, 0, std::min(itemCount, visibleSlots) - 1);

        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_I))
        {
            Close();
            return;
        }

        if (itemCount <= 0)
            return;

        if (IsKeyPressed(KEY_RIGHT))
            selectedItem = (selectedItem + 1) % std::min(itemCount, visibleSlots);
        if (IsKeyPressed(KEY_LEFT))
            selectedItem = (selectedItem - 1 + std::min(itemCount, visibleSlots))
                % std::min(itemCount, visibleSlots);
        if (IsKeyPressed(KEY_DOWN))
            selectedItem = (selectedItem + GRID_COLUMNS) % std::min(itemCount, visibleSlots);
        if (IsKeyPressed(KEY_UP))
            selectedItem = (selectedItem - GRID_COLUMNS + std::min(itemCount, visibleSlots))
                % std::min(itemCount, visibleSlots);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            const Vector2 mouse = GetMousePosition();
            for (int i = 0; i < std::min(itemCount, visibleSlots); ++i)
            {
                const int column = i % GRID_COLUMNS;
                const int row = i / GRID_COLUMNS;
                const Rectangle slot = {
                    static_cast<float>(GRID_X + column * (SLOT_SIZE + SLOT_GAP)),
                    static_cast<float>(GRID_Y + row * (SLOT_SIZE + SLOT_GAP)),
                    static_cast<float>(SLOT_SIZE),
                    static_cast<float>(SLOT_SIZE)
                };

                if (CheckCollisionPointRec(mouse, slot))
                {
                    selectedItem = i;
                    break;
                }
            }
        }
    }

    void Draw(const Inventory& inventory)
    {
        if (!inventoryOpen)
            return;

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.58f));
        DrawRectangle(PANEL_X, PANEL_Y, PANEL_WIDTH, PANEL_HEIGHT, Color{ 24, 31, 35, 248 });
        DrawRectangleLines(PANEL_X, PANEL_Y, PANEL_WIDTH, PANEL_HEIGHT, GOLD);
        DrawText("ADVENTURER INVENTORY", PANEL_X + 30, PANEL_Y + 22, 26, GOLD);
        DrawText("I / ESC: CLOSE     ARROWS: SELECT", PANEL_X + 30, PANEL_Y + 58, 15, LIGHTGRAY);

        const auto& items = inventory.GetItems();
        const int visibleSlots = GRID_COLUMNS * GRID_ROWS;

        for (int i = 0; i < visibleSlots; ++i)
        {
            const int column = i % GRID_COLUMNS;
            const int row = i / GRID_COLUMNS;
            const int x = GRID_X + column * (SLOT_SIZE + SLOT_GAP);
            const int y = GRID_Y + row * (SLOT_SIZE + SLOT_GAP);
            const Rectangle slot = {
                static_cast<float>(x), static_cast<float>(y),
                static_cast<float>(SLOT_SIZE), static_cast<float>(SLOT_SIZE)
            };

            DrawRectangleRec(slot, Color{ 43, 53, 57, 255 });
            DrawRectangleLinesEx(slot, 2.0f,
                i == selectedItem ? GOLD : Color{ 93, 108, 108, 255 });

            if (i < static_cast<int>(items.size()))
            {
                const ItemStack& item = items[i];
                DrawText(item.displayName.c_str(), x + 5, y + 12, 11, RAYWHITE);
                DrawText(TextFormat("x%d", item.quantity), x + 8, y + 49, 17, GOLD);
            }
            else
            {
                DrawText("-", x + 32, y + 27, 20, DARKGRAY);
            }
        }

        const int detailsX = 760;
        const int detailsY = 190;
        DrawRectangle(detailsX, detailsY, 235, 334, Color{ 34, 43, 47, 255 });
        DrawRectangleLines(detailsX, detailsY, 235, 334, Color{ 93, 108, 108, 255 });
        DrawText("ITEM DETAILS", detailsX + 18, detailsY + 18, 18, GOLD);

        if (!items.empty() && selectedItem < static_cast<int>(items.size())
            && selectedItem < visibleSlots)
        {
            const ItemStack& item = items[selectedItem];
            DrawText(item.displayName.c_str(), detailsX + 18, detailsY + 64, 18, RAYWHITE);
            DrawText(TextFormat("Quantity: %d", item.quantity),
                detailsX + 18, detailsY + 102, 16, LIGHTGRAY);
            DrawText(TextFormat("Stack limit: %d", item.maxStack),
                detailsX + 18, detailsY + 130, 16, LIGHTGRAY);
            DrawText("Item ID:", detailsX + 18, detailsY + 180, 14, LIGHTGRAY);
            DrawText(item.itemId.c_str(), detailsX + 18, detailsY + 202, 13, RAYWHITE);
        }
        else
        {
            DrawText("No item selected.", detailsX + 18, detailsY + 72, 16, LIGHTGRAY);
            DrawText("Gather resources to", detailsX + 18, detailsY + 108, 14, LIGHTGRAY);
            DrawText("fill your inventory.", detailsX + 18, detailsY + 130, 14, LIGHTGRAY);
        }

        DrawText(TextFormat("Slots: %d / %d",
            inventory.GetUsedSlots(), inventory.GetCapacity()),
            PANEL_X + 30, PANEL_Y + PANEL_HEIGHT - 35, 17, RAYWHITE);
    }
}
