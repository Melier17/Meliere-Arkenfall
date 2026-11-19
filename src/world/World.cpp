#include "World.h"

namespace
{
    constexpr Color WORLD_BACKGROUND = { 32, 48, 45, 255 };
    constexpr Color WORLD_FLOOR = { 54, 77, 62, 255 };
    constexpr Color GRID_COLOR = { 65, 88, 72, 255 };
    constexpr Color OBSTACLE_COLOR = { 92, 76, 61, 255 };
    constexpr Color OBSTACLE_BORDER = { 143, 119, 88, 255 };
}

World::World()
    : obstacles_{{
        { 520.0f, 360.0f, 220.0f, 80.0f },
        { 980.0f, 620.0f, 100.0f, 260.0f },
        { 1450.0f, 420.0f, 300.0f, 90.0f },
        { 1760.0f, 1050.0f, 120.0f, 260.0f },
        { 650.0f, 1180.0f, 340.0f, 100.0f }
    }}
{
}

Rectangle World::GetBounds(Vector2 position, Vector2 size) const
{
    return { position.x, position.y, size.x, size.y };
}

void World::MovePlayer(Vector2& position, Vector2 size,
                       Vector2 direction, float distance) const
{
    // Resolve horizontal movement independently.
    position.x += direction.x * distance;
    Rectangle bounds = GetBounds(position, size);

    for (const Rectangle& obstacle : obstacles_)
    {
        if (CheckCollisionRecs(bounds, obstacle))
        {
            if (direction.x > 0.0f) position.x = obstacle.x - size.x;
            if (direction.x < 0.0f) position.x = obstacle.x + obstacle.width;
            bounds = GetBounds(position, size);
        }
    }

    // Resolve vertical movement independently.
    position.y += direction.y * distance;
    bounds = GetBounds(position, size);

    for (const Rectangle& obstacle : obstacles_)
    {
        if (CheckCollisionRecs(bounds, obstacle))
        {
            if (direction.y > 0.0f) position.y = obstacle.y - size.y;
            if (direction.y < 0.0f) position.y = obstacle.y + obstacle.height;
            bounds = GetBounds(position, size);
        }
    }
}

void World::ClampToBounds(Vector2& position, Vector2 size) const
{
    if (position.x < 0.0f) position.x = 0.0f;
    if (position.y < 0.0f) position.y = 0.0f;

    const float maxX = WORLD_WIDTH - size.x;
    const float maxY = WORLD_HEIGHT - size.y;

    if (position.x > maxX) position.x = maxX;
    if (position.y > maxY) position.y = maxY;
}

void World::Draw() const
{
    ClearBackground(WORLD_BACKGROUND);

    DrawRectangle(0, 0, static_cast<int>(WORLD_WIDTH),
                  static_cast<int>(WORLD_HEIGHT), WORLD_FLOOR);

    for (int x = 0; x <= static_cast<int>(WORLD_WIDTH); x += 100)
    {
        DrawLine(x, 0, x, static_cast<int>(WORLD_HEIGHT), GRID_COLOR);
    }

    for (int y = 0; y <= static_cast<int>(WORLD_HEIGHT); y += 100)
    {
        DrawLine(0, y, static_cast<int>(WORLD_WIDTH), y, GRID_COLOR);
    }

    DrawRectangleLines(0, 0, static_cast<int>(WORLD_WIDTH),
                       static_cast<int>(WORLD_HEIGHT), GOLD);

    for (const Rectangle& obstacle : obstacles_)
    {
        DrawRectangleRec(obstacle, OBSTACLE_COLOR);
        DrawRectangleLinesEx(obstacle, 3.0f, OBSTACLE_BORDER);
    }
}
