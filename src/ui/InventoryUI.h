#pragma once

#include "raylib.h"
#include "systems/Inventory.h"

namespace InventoryUI
{
    void Toggle();
    void Close();
    bool IsOpen();
    void Update(const Inventory& inventory);
    void Draw(const Inventory& inventory);
}
