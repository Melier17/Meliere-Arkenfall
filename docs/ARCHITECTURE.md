# Arkenfall — Technical Architecture

**Version:** 0.1.0  
**Status:** First modular source layout created; build verification pending.

## Current technical baseline

- C++17
- raylib 5.0
- CMake
- Desktop prototype, single-player and local only

## Current source organization

```text
src/
├── core/
│   ├── Game.cpp
│   └── Game.h
├── entities/
│   ├── Player.cpp
│   └── Player.h
├── world/
│   ├── World.cpp
│   └── World.h
└── main.cpp
```

The original root-level `main.cpp` is being kept temporarily as a legacy reference. The active CMake target now uses `src/main.cpp`.

## Module responsibilities

- **Game:** owns window initialization, the main loop, frame updates, camera tracking, drawing order, and window shutdown.
- **Player:** stores player state, reads keyboard movement, normalizes diagonal movement, and draws the player placeholder.
- **World:** owns world dimensions and static obstacles, resolves basic axis-separated collisions, clamps the player to world bounds, and renders the test environment.
- **Entry point:** creates the Game object and starts its run loop.

## Current prototype behavior

- Eight-direction movement with WASD or arrow keys.
- Delta-time-based movement.
- Camera follows the player.
- Bounded test world with a grid and static obstacles.
- Basic rectangle collision handling.
- HUD identifying the prototype build.

## Current limitations and verification

- The player is a colored rectangle, not a final character sprite.
- The test map and obstacles are hard-coded.
- Collision response is a simple prototype, not a complete physics system.
- There is no animation, combat, inventory, persistence, or networking.
- The camera follows the player directly; smoothing and world-edge clamping are future improvements.
- The modular source has been committed remotely but has not been compiled or run in the current workflow. A local CMake build and runtime test are required before marking it as verified.

## Planned extensions

Potential next modules include game states/scenes, input abstraction, interaction, inventory, persistence, and data-driven world content. These are not implemented yet.

## Architectural rules

1. Keep rendering separate from gameplay rules as the codebase expands.
2. Use delta time for movement and timed simulation.
3. Keep world coordinates separate from screen coordinates.
4. Keep gameplay data independent from visual presentation where practical.
5. Introduce networking only after the offline gameplay loop is stable.
6. When multiplayer is added, the server must validate inventory, currency, rewards, and guild operations.
