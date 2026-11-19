#pragma once

#include "raylib.h"

#include <array>

class World
{
public:
    World();

    void Draw() const;
    void MovePlayer(Vector2& position, Vector2 size,
                    Vector2 direction, float distance) const;
    void ClampToBounds(Vector2& position, Vector2 size) const;

private:
    static constexpr float WORLD_WIDTH = 2400.0f;
    static constexpr float WORLD_HEIGHT = 1600.0f;

    std::array<Rectangle, 5> obstacles_;

    Rectangle GetBounds(Vector2 position, Vector2 size) const;
};
