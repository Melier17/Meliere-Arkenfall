#pragma once

#include "entities/Character.h"
#include "raylib.h"

#include <string>

class SaveSystem
{
public:
    static bool SaveCharacter(const Character& character,
                              const std::string& filePath);
    static bool LoadCharacter(Character& character,
                              const std::string& filePath);
    static bool SavePlayerPosition(Vector2 position,
                                   const std::string& filePath);
    static bool LoadPlayerPosition(Vector2& position,
                                   const std::string& filePath);
};
