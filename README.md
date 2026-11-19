# MELIERE — ARKENFALL

**A Meliere Games Production**  
**Tagline:** Your World. Your Legend.

Arkenfall is an original 2D top-down fantasy adventure RPG in development. Its long-term design combines open-world exploration, survival, character progression, professions, companions, guild communities, player-driven trade, and instanced dungeons.

## Project status

- **Version:** 0.1.0 — foundation prototype
- **Status:** Early development
- **Language:** C++17
- **Framework:** raylib 5.0
- **Build system:** CMake
- **Development branch:** `arkenfall/rebuild-v0.1`

The Game Design Document describes the intended direction. Features are not considered implemented until code exists and has been tested.

## Current milestone — playable foundation

The first prototype focuses on:
1. Game window and main loop.
2. Eight-direction player movement.
3. Frame-rate-independent movement.
4. Camera follow.
5. A bounded test world.
6. Basic obstacle collisions.

Online multiplayer, persistence, guilds, economy, procedural dungeons, and other advanced systems belong to later milestones.

## Repository layout

```text
.
├── docs/
│   ├── GDD.md
│   ├── ROADMAP.md
│   └── ARCHITECTURE.md
├── CMakeLists.txt
├── main.cpp
└── README.md
```

## Requirements
- CMake 3.11 or newer
- A C++17-compatible compiler
- raylib 5.0 (downloaded by CMake FetchContent)

## Development principles
- Keep planned, implemented, and tested features clearly distinguished.
- Prefer small, reviewable changes.
- Keep gameplay systems modular.
- Validate multiplayer-sensitive operations on the server when online systems are introduced.
- Avoid pay-to-win progression.

---

**MELIERE — ARKENFALL**  
*Your World. Your Legend.*
