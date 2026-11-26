#pragma once

#include "systems/Inventory.h"

#include <string>

enum class CharacterRace { Human, Elf, Dwarf };
enum class CharacterArchetype { Adventurer, Vanguard, Arcanist };

class Character
{
public:
    Character();

    const std::string& GetName() const;
    void SetName(const std::string& name);
    CharacterRace GetRace() const;
    void SetRace(CharacterRace race);
    CharacterArchetype GetArchetype() const;
    void SetArchetype(CharacterArchetype archetype);
    int GetLevel() const;
    int GetExperience() const;
    void SetProgression(int level, int experience);
    Inventory& GetInventory();
    const Inventory& GetInventory() const;
    bool IsCreated() const;
    bool Create();

private:
    std::string name_;
    CharacterRace race_;
    CharacterArchetype archetype_;
    int level_;
    int experience_;
    bool created_;
    Inventory inventory_;
};
