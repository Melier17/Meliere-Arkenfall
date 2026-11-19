# Arkenfall — Technical Architecture

**Version:** 0.1.0  
**Status:** Initial prototype architecture

## Current technical baseline

- C++17
- raylib 5.0
- CMake
- Desktop prototype, single-player and local only

## Prototype responsibilities

The first prototype keeps the implementation intentionally small:

- **Entry point:** initializes the window and owns the main loop.
- **Player state:** stores position, movement speed, size, and display color.
- **Input/update:** reads movement input and updates the player using frame delta time.
- **Collision:** checks the player rectangle against static obstacle rectangles.
- **Camera:** follows the player in world coordinates.
- **Rendering:** draws the test world, obstacles, player placeholder, and HUD.

## Current limitations

- The player is a colored rectangle, not a final character sprite.
- The test map and obstacles are hard-coded.
- Collision response is a simple prototype and is not a complete physics system.
- There is no animation, combat, inventory, persistence, or networking.
- The camera currently follows the player directly; smoothing and world-edge clamping are future improvements.
- This source has not been compiled or run in the current remote editing workflow. A local build is required before marking the milestone as tested.

## Planned source organization

When the prototype grows, split responsibilities into focused modules:

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
├── systems/
│   ├── InputSystem.cpp
│   └── CollisionSystem.cpp
└── main.cpp
```

The structure above is a target layout, not the current repository contents.

## Architectural rules

1. Keep rendering separate from gameplay rules as the codebase expands.
2. Use delta time for movement and timed simulation.
3. Keep world coordinates separate from screen coordinates.
4. Keep gameplay data independent from visual presentation where practical.
5. Introduce networking only after the offline gameplay loop is stable.
6. When multiplayer is added, the server must validate inventory, currency, rewards, and guild operations.
