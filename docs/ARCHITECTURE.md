# Arkenfall — Technical Architecture

**Version:** 0.1.0  
**Status:** Modular foundation and first navigation states implemented; build verification pending.

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
│   ├── Game.h
│   └── GameState.h
├── ui/
│   ├── MenuUI.cpp
│   └── MenuUI.h
├── entities/
│   ├── Character.cpp
│   ├── Character.h
│   ├── Player.cpp
│   └── Player.h
├── world/
│   ├── World.cpp
│   └── World.h
└── main.cpp
```

The original root-level main.cpp is being kept temporarily as a legacy reference. The active CMake target uses src/main.cpp.

## Module responsibilities

- **Game:** owns window initialization, the main loop, state transitions, frame updates, camera tracking, drawing order, and window shutdown.
- **GameState:** defines the available high-level screens: MainMenu, CharacterCreation, Playing, Paused, and ExitConfirmation.
- **MenuUI:** provides reusable menu button bounds, mouse hit-testing, button rendering, centered screen titles, and the menu background. It contains presentation helpers rather than game-state decisions.
- **Character:** stores the character name, provisional race/archetype selections, level and experience. Creation validates a non-empty name; the current sample race/archetype values are placeholders and not final GDD decisions.
- **Player:** stores player state, reads keyboard movement, normalizes diagonal movement, and draws the player placeholder.
- **World:** owns world dimensions and static obstacles, resolves basic axis-separated collisions, clamps the player to world bounds, and renders the test environment.
- **Entry point:** creates the Game object and starts its run loop.

## Navigation and controls

- **Main menu:** Enter or Start Game opens character creation; Escape or Exit opens the exit confirmation.\n- **Character creation:** type a name, use Left/Right or the on-screen arrows to cycle provisional races, Tab or the on-screen arrow to cycle archetypes, Enter or Create to confirm, and Escape or Back to return.
- **Playing:** WASD or arrow keys move the player; Escape opens the pause screen.
- **Paused:** Escape or R resumes; M returns to the main menu; Q opens exit confirmation.
- **Exit confirmation:** Y confirms exit; N or Escape cancels. Mouse buttons are also available on the menu screens.

The pause state does not call the player's update function, so movement is suspended while paused. Returning from pause to the game preserves the current player position.

## Current prototype behavior

- Eight-direction movement with normalized diagonal speed.
- Delta-time-based movement.
- Camera follows the player.
- Bounded test world with a grid and static obstacles.
- Basic rectangle collision handling.
- Main menu, pause screen, and exit confirmation.
- Simple keyboard and mouse UI interaction.\n- Initial character creation screen connected to the Character model, with name validation and provisional selections.
- Reusable menu presentation module separated from the Game controller.

## Current limitations and verification

- The player is a colored rectangle, not a final character sprite.
- The test map and obstacles are hard-coded.
- Collision response is a simple prototype, not a complete physics system.
- There is no animation, combat, inventory, persistence, or networking.
- The camera follows the player directly; smoothing and world-edge clamping are future improvements.
- Window-manager close requests still close the application directly.
- The modular source has been committed remotely but has not been compiled or run in the current workflow. A local CMake build and runtime test are required before marking it as verified.

## Planned extensions

Potential next modules include input abstraction, interaction, inventory, persistence, and data-driven world content. These are not implemented yet.

## Architectural rules

1. Keep rendering separate from gameplay rules as the codebase expands.
2. Use delta time for movement and timed simulation.
3. Keep world coordinates separate from screen coordinates.
4. Keep gameplay data independent from visual presentation where practical.
5. Introduce networking only after the offline gameplay loop is stable.
6. When multiplayer is added, the server must validate inventory, currency, rewards, and guild operations.
