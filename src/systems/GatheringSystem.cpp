#include "GatheringSystem.h"

#include <cmath>
#include <limits>

namespace
{
    constexpr float GATHER_DISTANCE = 92.0f;
    constexpr float GATHER_DISTANCE_SQUARED = GATHER_DISTANCE * GATHER_DISTANCE;
}

GatheringSystem::GatheringSystem()
    : nodes_{
        { "wood", "Wood", { 1280.0f, 820.0f }, 8, Color{ 117, 78, 45, 255 } },
        { "stone", "Stone", { 1080.0f, 930.0f }, 8, Color{ 145, 150, 151, 255 } },
        { "herb", "Herbs", { 1280.0f, 1010.0f }, 6, Color{ 72, 170, 92, 255 } },
        { "iron_ore", "Iron Ore", { 1390.0f, 960.0f }, 5, Color{ 130, 105, 95, 255 } }
    },
      lastMessage_("Explore nearby resource nodes and press E to gather.")
{
}

int GatheringSystem::FindNearestNode(Vector2 playerCenter) const
{
    int nearestIndex = -1;
    float nearestDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < static_cast<int>(nodes_.size()); ++i)
    {
        const ResourceNode& node = nodes_[i];
        if (node.remaining <= 0)
            continue;

        const float dx = node.position.x - playerCenter.x;
        const float dy = node.position.y - playerCenter.y;
        const float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared <= GATHER_DISTANCE_SQUARED
            && distanceSquared < nearestDistance)
        {
            nearestDistance = distanceSquared;
            nearestIndex = i;
        }
    }

    return nearestIndex;
}

bool GatheringSystem::TryGather(Vector2 playerCenter, Inventory& inventory)
{
    const int index = FindNearestNode(playerCenter);
    if (index < 0)
    {
        lastMessage_ = "No resource nearby. Move closer to a node.";
        return false;
    }

    ResourceNode& node = nodes_[index];
    if (!inventory.AddItem(node.itemId, node.displayName, 1))
    {
        lastMessage_ = "Inventory full. Make room before gathering.";
        return false;
    }

    --node.remaining;
    lastMessage_ = "Collected 1 " + node.displayName + ".";
    if (node.remaining == 0)
        lastMessage_ += " This node is depleted.";

    return true;
}

void GatheringSystem::Draw(Vector2 playerCenter) const
{
    for (const ResourceNode& node : nodes_)
    {
        if (node.remaining <= 0)
            continue;

        DrawCircleV(node.position, 19.0f, node.color);
        DrawCircleLines(static_cast<int>(node.position.x),
                        static_cast<int>(node.position.y), 20.0f, RAYWHITE);
        DrawText(node.displayName.c_str(),
                 static_cast<int>(node.position.x) - 34,
                 static_cast<int>(node.position.y) + 27, 14, RAYWHITE);
    }

    const int nearest = FindNearestNode(playerCenter);
    if (nearest >= 0)
    {
        const ResourceNode& node = nodes_[nearest];
        DrawText("Press E to gather",
                 static_cast<int>(node.position.x) - 60,
                 static_cast<int>(node.position.y) - 48, 16, GOLD);
    }
}

const std::string& GatheringSystem::GetLastMessage() const
{
    return lastMessage_;
}
