#pragma once

#include "raylib.h"
#include "systems/Inventory.h"

#include <string>
#include <vector>

struct ResourceNode
{
    std::string itemId;
    std::string displayName;
    Vector2 position;
    int remaining;
    Color color;
};

class GatheringSystem
{
public:
    GatheringSystem();

    bool TryGather(Vector2 playerCenter, Inventory& inventory);
    void Draw(Vector2 playerCenter) const;
    const std::string& GetLastMessage() const;

private:
    std::vector<ResourceNode> nodes_;
    std::string lastMessage_;

    int FindNearestNode(Vector2 playerCenter) const;
};
