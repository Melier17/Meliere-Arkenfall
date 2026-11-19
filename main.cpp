#include "raylib.h"

#include <cmath>

namespace
{
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int SCREEN_HEIGHT = 720;

    constexpr float WORLD_WIDTH = 2400.0f;
    constexpr float WORLD_HEIGHT = 1600.0f;

    constexpr float PLAYER_SIZE = 32.0f;
    constexpr float PLAYER_SPEED = 220.0f;

    struct Player
    {
        Vector2 position;
        float speed;
        float size;
        Color color;
    };

    const Rectangle obstacles[] = {
        { 520.0f, 360.0f, 220.0f, 80.0f },
        { 980.0f, 620.0f, 100.0f, 260.0f },
        { 1450.0f, 420.0f, 300.0f, 90.0f },
        { 1760.0f, 1050.0f, 120.0f, 260.0f },
        { 650.0f, 1180.0f, 340.0f, 100.0f }
    };

    Rectangle GetPlayerBounds(const Player& player)
    {
        return {
            player.position.x,
            player.position.y,
            player.size,
            player.size
        };
    }

    void UpdatePlayer(Player& player, float deltaTime)
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

        const float movement = player.speed * deltaTime;

        // Resolve horizontal movement independently.
        player.position.x += direction.x * movement;
        Rectangle bounds = GetPlayerBounds(player);

        for (const Rectangle& obstacle : obstacles)
        {
            if (CheckCollisionRecs(bounds, obstacle))
            {
                if (direction.x > 0.0f) player.position.x = obstacle.x - player.size;
                if (direction.x < 0.0f) player.position.x = obstacle.x + obstacle.width;
                bounds = GetPlayerBounds(player);
            }
        }

        // Resolve vertical movement independently.
        player.position.y += direction.y * movement;
        bounds = GetPlayerBounds(player);

        for (const Rectangle& obstacle : obstacles)
        {
            if (CheckCollisionRecs(bounds, obstacle))
            {
                if (direction.y > 0.0f) player.position.y = obstacle.y - player.size;
                if (direction.y < 0.0f) player.position.y = obstacle.y + obstacle.height;
                bounds = GetPlayerBounds(player);
            }
        }

        // Keep the player inside the world.
        if (player.position.x < 0.0f) player.position.x = 0.0f;
        if (player.position.y < 0.0f) player.position.y = 0.0f;

        const float maxX = WORLD_WIDTH - player.size;
        const float maxY = WORLD_HEIGHT - player.size;

        if (player.position.x > maxX) player.position.x = maxX;
        if (player.position.y > maxY) player.position.y = maxY;
    }

    void DrawWorld(const Player& player)
    {
        ClearBackground(Color{ 32, 48, 45, 255 });

        // World floor.
        DrawRectangle(0, 0, static_cast<int>(WORLD_WIDTH),
                      static_cast<int>(WORLD_HEIGHT), Color{ 54, 77, 62, 255 });

        // Subtle world grid for the prototype.
        for (int x = 0; x <= static_cast<int>(WORLD_WIDTH); x += 100)
        {
            DrawLine(x, 0, x, static_cast<int>(WORLD_HEIGHT),
                     Color{ 65, 88, 72, 255 });
        }

        for (int y = 0; y <= static_cast<int>(WORLD_HEIGHT); y += 100)
        {
            DrawLine(0, y, static_cast<int>(WORLD_WIDTH), y,
                     Color{ 65, 88, 72, 255 });
        }

        // World boundary.
        DrawRectangleLines(0, 0, static_cast<int>(WORLD_WIDTH),
                           static_cast<int>(WORLD_HEIGHT), GOLD);

        // Obstacles.
        for (const Rectangle& obstacle : obstacles)
        {
            DrawRectangleRec(obstacle, Color{ 92, 76, 61, 255 });
            DrawRectangleLinesEx(obstacle, 3.0f, Color{ 143, 119, 88, 255 });
        }

        // Player placeholder.
        DrawRectangleV(player.position, { player.size, player.size }, player.color);
        DrawRectangleLines(
            static_cast<int>(player.position.x),
            static_cast<int>(player.position.y),
            static_cast<int>(player.size),
            static_cast<int>(player.size),
            RAYWHITE
        );
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MELIERE - ARKENFALL");
    SetTargetFPS(60);

    Player player = {
        { WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f },
        PLAYER_SPEED,
        PLAYER_SIZE,
        MAROON
    };

    Camera2D camera = { 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.target = {
        player.position.x + player.size / 2.0f,
        player.position.y + player.size / 2.0f
    };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        UpdatePlayer(player, deltaTime);

        camera.target = {
            player.position.x + player.size / 2.0f,
            player.position.y + player.size / 2.0f
        };

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera);
                DrawWorld(player);
            EndMode2D();

            DrawRectangle(12, 12, 390, 72, Fade(BLACK, 0.65f));
            DrawText("ARKENFALL - PROTOTYPE v0.1.0", 24, 22, 20, GOLD);
            DrawText("Move: WASD / Arrow keys", 24, 50, 16, RAYWHITE);
            DrawFPS(SCREEN_WIDTH - 90, 16);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
