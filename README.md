# Billy Engine

Some kind of 2D game engine, written in C++17 using SDL2 and EnTT to use in future projects.

Requires SDL2 and SDL2_ttf to be installed globally.

Developed on Linux but _should_ work on other platforms.

## How to use

Just bring it in using git submodules or CMake's `FetchContent` and `#include <BillyEngine.hpp>`.

Entities are just classes derived from `ScriptableEntity`. Use `SCRIPTABLE_ENTITY` macro to create the right constructor (other constructors won't be called, use `OnCreate`).

## Build

This repository contains the source for the engine itself that gets compiled to a dynamic library and a little demo.
By default both are built but the demo can be disabled passing `-DCOMPILE_DEMO=OFF` to `cmake`.

```sh
cmake -S . -B build
cmake --build build
```
