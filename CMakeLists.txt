cmake_minimum_required(VERSION 3.11)

project(MeliereArkenfall VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

add_executable(arkenfall
    src/main.cpp
    src/core/Game.cpp
    src/core/SaveSystem.cpp
    src/core/SaveSystem.h
    src/core/Game.h
    src/core/GameState.h
    src/ui/MenuUI.cpp
    src/ui/MenuUI.h
    src/systems/Inventory.cpp
    src/systems/Inventory.h
    src/entities/Character.cpp
    src/entities/Character.h
    src/entities/Player.cpp
    src/entities/Player.h
    src/world/World.cpp
    src/world/World.h
)

target_include_directories(arkenfall PRIVATE
    src
    src/core
    src/entities
    src/systems
    src/world
    src/ui
)

target_link_libraries(arkenfall PRIVATE raylib)
