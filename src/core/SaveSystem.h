#pragma once

#include "entities/Character.h"

#include <string>

class SaveSystem
{
public:
    static bool SaveCharacter(const Character& character,
                              const std::string& filePath);
    static bool LoadCharacter(Character& character,
                              const std::string& filePath);
};
