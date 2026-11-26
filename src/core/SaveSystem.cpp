#include "SaveSystem.h"

#include <fstream>
#include <limits>

namespace
{
    constexpr int SAVE_VERSION = 1;
}

bool SaveSystem::SaveCharacter(const Character& character,
                               const std::string& filePath)
{
    if (!character.IsCreated() || filePath.empty())
        return false;

    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open())
        return false;

    file << SAVE_VERSION << '\n'
         << character.GetName() << '\n'
         << static_cast<int>(character.GetRace()) << '\n'
         << static_cast<int>(character.GetArchetype()) << '\n'
         << character.GetLevel() << '\n'
         << character.GetExperience() << '\n';

    return file.good();
}

bool SaveSystem::LoadCharacter(Character& character,
                               const std::string& filePath)
{
    if (filePath.empty())
        return false;

    std::ifstream file(filePath);
    if (!file.is_open())
        return false;

    int version = 0;
    int race = 0;
    int archetype = 0;
    int level = 1;
    int experience = 0;
    std::string name;

    if (!(file >> version) || version != SAVE_VERSION)
        return false;

    file.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::getline(file, name)
        || !(file >> race >> archetype >> level >> experience))
        return false;

    if (race < 0 || race > 2 || archetype < 0 || archetype > 2
        || level < 1 || experience < 0)
        return false;

    character.SetName(name);
    character.SetRace(static_cast<CharacterRace>(race));
    character.SetArchetype(static_cast<CharacterArchetype>(archetype));

    character.SetProgression(level, experience);
    return character.Create();
}

bool SaveSystem::SavePlayerPosition(Vector2 position,
                                    const std::string& filePath)
{
    if (filePath.empty())
        return false;

    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open())
        return false;

    file << position.x << '\\n' << position.y << '\\n';
    return file.good();
}

bool SaveSystem::LoadPlayerPosition(Vector2& position,
                                    const std::string& filePath)
{
    if (filePath.empty())
        return false;

    std::ifstream file(filePath);
    if (!file.is_open())
        return false;

    Vector2 loadedPosition{};
    if (!(file >> loadedPosition.x >> loadedPosition.y))
        return false;

    if (loadedPosition.x < 0.0f || loadedPosition.y < 0.0f
        || loadedPosition.x > 2368.0f || loadedPosition.y > 1568.0f)
        return false;

    position = loadedPosition;
    return true;
}
