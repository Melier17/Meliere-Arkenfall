#include "Player.h"

#include "World.h"

#include <cmath>

namespace
{
    constexpr float PLAYER_SIZE = 32.0f;
    constexpr float PLAYER_SPEED = 220.0f;
}

Player::Player()
    : position_{ 1200.0f, 800.0f },
      speed_(PLAYER_SPEED),
      size_(PLAYER_SIZE),
      color_(MAROON)
{
}

void Player::Update(float deltaTime, const World& world)
{
    Vector2 direction = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1.0f;

    const float length = std::sqrt(
        direction.x * direction.x + direction.y * direction.y
    );

    if (length > 0.0f)
    {
        direction.x /= length;
        direction.y /= length;
    }

    world.MovePlayer(position_, { size_, size_ }, direction, speed_ * deltaTime);
    world.ClampToBounds(position_, { size_, size_ });
}

void Player::Draw() const
{
    DrawRectangleV(position_, { size_, size_ }, color_);
    DrawRectangleLines(
        static_cast<int>(position_.x),
        static_cast<int>(position_.y),
        static_cast<int>(size_),
        static_cast<int>(size_),
        RAYWHITE
    );
}

Vector2 Player::GetCenter() const
{
    return {
        position_.x + size_ / 2.0f,
        position_.y + size_ / 2.0f
    };
}

Vector2 Player::GetPosition() const
{
    return position_;
}

void Player::SetPosition(Vector2 position)
{
    position_.x = position.x;
    position_.y = position.y;
}
