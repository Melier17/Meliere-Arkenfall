#pragma once

#include "raylib.h"

class World;

class Player
{
public:
    Player();

    void Update(float deltaTime, const World& world);
    void Draw() const;

    Vector2 GetCenter() const;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 position);

private:
    Vector2 position_;
    float speed_;
    float size_;
    Color color_;
};
