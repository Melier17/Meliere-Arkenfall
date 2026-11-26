#include "Character.h"

#include <algorithm>
#include <cctype>

Character::Character()
    : name_(""), race_(CharacterRace::Human),
      archetype_(CharacterArchetype::Adventurer),
      level_(1), experience_(0), created_(false)
{
}

const std::string& Character::GetName() const { return name_; }

void Character::SetName(const std::string& name)
{
    name_ = name;
    name_.erase(name_.begin(), std::find_if(name_.begin(), name_.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
    name_.erase(std::find_if(name_.rbegin(), name_.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), name_.end());

    if (name_.size() > 20)
        name_.resize(20);
}

CharacterRace Character::GetRace() const { return race_; }
void Character::SetRace(CharacterRace race) { race_ = race; }

CharacterArchetype Character::GetArchetype() const { return archetype_; }
void Character::SetArchetype(CharacterArchetype archetype) { archetype_ = archetype; }

int Character::GetLevel() const { return level_; }
int Character::GetExperience() const { return experience_; }

void Character::SetProgression(int level, int experience)
{
    level_ = level < 1 ? 1 : level;
    experience_ = experience < 0 ? 0 : experience;
}

Inventory& Character::GetInventory() { return inventory_; }

const Inventory& Character::GetInventory() const { return inventory_; }

bool Character::IsCreated() const { return created_; }

bool Character::Create()
{
    if (name_.empty())
        return false;

    created_ = true;
    return true;
}
