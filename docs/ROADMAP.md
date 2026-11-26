# Arkenfall — Development Roadmap

**Document version:** 0.1.0  
**Status:** Navigation state flow implemented in source; build verification pending.

This roadmap separates the long-term game vision from the first technical deliverables. Dates and estimates are intentionally omitted until the scope and development environment are validated.

## Phase 0 — Repository and technical foundation

- [x] Identify the existing C++17 / raylib / CMake project.
- [x] Preserve the existing Game Design Document.
- [x] Create an isolated development branch for the Arkenfall reorganization.
- [x] Standardize project naming and build target.
- [x] Review and correct the initial source-level issues.
- [x] Add a GitHub Actions Linux build workflow for reproducible compile checks.
- [ ] Establish a clean, reproducible build (awaiting workflow result).

## Phase 1 — Playable 2D foundation (v0.1)

- [x] Initialize the game window and main loop.
- [x] Implement a player entity with position and movement speed.
- [x] Support eight-direction movement.
- [x] Normalize diagonal movement.
- [x] Add a camera that follows the player.
- [x] Create a bounded test world.
- [x] Add static obstacles and basic collision handling.
- [x] Separate input/update and world drawing into dedicated functions.
- [ ] Compile and test the prototype on a supported desktop environment.

## Phase 2 — Core gameplay structure

- [x] Split the prototype into modular source files.
- [x] Introduce a central Game module to own the game loop and lifecycle.
- [x] Separate Player and World responsibilities.
- [x] Define the initial MainMenu, Playing, Paused, and ExitConfirmation states.
- [x] Add keyboard and mouse navigation for the initial menus.
- [x] Suspend player updates while the game is paused.
- [x] Extract reusable menu UI components into a dedicated module.
- [ ] Expand game states/scenes for future systems.
- [x] Create the initial Character data model (name, provisional race/archetype, level, experience).
- [x] Connect the first character creation screen to the Character model.
- [x] Support keyboard and mouse selection/confirmation in character creation.
- [x] Persist character identity and progression to versioned local save data.
- [x] Save and restore the player's world position.
- [ ] Compile and test save/load behavior on a supported desktop environment.
- [ ] Add data-driven player attributes.
- [ ] Define a basic interaction system.
- [x] Create a modular inventory data model with capacity, stack limits, add/remove, and quantity queries.
- [x] Attach the inventory model to each Character instance.
- [x] Integrate the inventory data model with the Character model.
- [x] Add an in-game inventory overlay with item slots, quantity display, and selection.
- [x] Add a simple interactive inventory prototype (open/close, mouse and keyboard selection).
- [ ] Add item descriptions, equipment actions, and inventory persistence.
- [ ] Add automated tests for inventory edge cases.
- [x] Establish a versioned local save-data format for character and position.
- [ ] Verify save-data compatibility and recovery through runtime tests.

## Phase 3 — World and progression prototypes

- [ ] Build a small exploration area.
- [ ] Prototype gathering and resource nodes.
- [ ] Prototype character experience and levels.
- [ ] Prototype one companion.
- [ ] Prototype one small dungeon encounter.

## Phase 4 — Online architecture research

- [ ] Define authoritative server responsibilities.
- [ ] Evaluate networking and persistence options.
- [ ] Design account, character, and session boundaries.
- [ ] Threat-model trading, inventory, rewards, and guild permissions.
- [ ] Build a separate network proof of concept before integrating it into the game.

## Production rule

A roadmap item is complete only when it has been implemented, reviewed, and tested. A design decision or a document entry does not mean the corresponding game feature exists. Items marked implemented still require a local build and runtime verification where indicated.
