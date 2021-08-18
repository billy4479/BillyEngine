# Billy Engine

Some kind of 2D game engine, written in C++17 using SDL2 and EnTT to be used in future projects.
I wanted a simple entity framework to display some graphics in my C++ applications and here it is.
It is not meant to be like Unreal / Unity / Godot,
the most similar thing I could find is [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

For now the rendering is done through SDL2 but in the future I'll probably switch to OpenGL.
So for now it requires SDL2 and SDL2_ttf to be installed globally.

I've developed it in Linux for Linux but _should_ work on other platforms as well.

There's still a lot of work to do, check out [TODO.md](TODO.md)

## How to use

Just bring it in using git submodules or CMake's `FetchContent` and `#include <BillyEngine.hpp>`.
Everything is under the `BillyEngine` namespace so it can became quite verbose.

`Application` is the base class for everything.
It takes care of the entity management and can give pointers to the `AssetManager` and the `Renderer`.

The `Entity` class is just an ID and a pointer so it's safe to copy it around.
It provide methots to add, get, check and remove components which are just `struct`s.

`ScriptableEntities` are entities with a custom behavior. 
The class, in turns, derives from `Entity` and has three methods to be overridden: `OnCreate`, `OnUpdate` and `OnDestroy`.
The constructor of this class has to be defined using the `SCRIPTABLE_ENTITY(ClassName)` macro.
Other constructors won't be called but you can use `OnCreate` for that.
Once you define you own class derived from it you can instantiate it using `CreateScriptableEntity<T>` on the application.

## Build

This repository contains the source for the engine itself that gets compiled to a dynamic library and a little demo.
By default both are built but the demo can be disabled passing `-DCOMPILE_DEMO=OFF` to `cmake`.

```sh
cmake -S . -B build
cmake --build build
```
