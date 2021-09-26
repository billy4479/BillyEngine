# Billy Engine

Some kind of 2D game engine, written in C++17 using SDL2 and EnTT to be used in future projects.
I wanted a simple entity framework to display some graphics in my C++ applications and here it is.
It is not meant to be like Unreal / Unity / Godot,
the most similar thing I could find is [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) and [raylib](https://github.com/raysan5/raylib). Thanks also to [TheCherno](https://www.youtube.com/c/TheChernoProject) for [Hazel](https://github.com/TheCherno/Hazel) from which I took a lot of inspiration.

I don't really care about the rendering part so for now it is done by SDL2
but maybe in the future I'll switch to OpenGL.
It requires SDL2, SDL2_ttf and SDL2_img to be installed globally. I want to remove those dependencies in the future because on Windows is a pain :)

I've developed it in Linux for Linux ~~but _should_ work on other platforms as well~~. Windows is WIP, OSX will probably not work.
I'm not targeting mobile.
WASM may be interesting but definitely not a priority.

There's still a lot of work to do, check out [TODO.md](TODO.md)

## How to use

Just bring it in using git submodules or CMake's `FetchContent` and `#include <BillyEngine.hpp>`.
Make sure that CMake can fine SDL2, SDL2_img and SDL_ttf.
Everything is under the `BillyEngine` namespace so it can became quite verbose.

`Application` is the base class for everything.
It is a wrapper around various managers used internally by the engine. If you need anything there is probably a method for that.

The `Entity` class is just an ID and a pointer so it's convenient to copy it around.
It provide methods to add, get, check and remove components which are just `class`es.

A `ScriptableEntity` is entity with a custom behavior.
The class is a wrapper around `Entity` and has three methods to be overridden: `OnCreate`, `OnUpdate` and `OnDestroy`.
The constructor of this class has to be defined using the `SCRIPTABLE_ENTITY(ClassName)` macro.
Other constructors won't be called but you can use `OnCreate` for that.
Once you define you own class derived from it you can instantiate it using `CreateScriptableEntity<T>` on the application.
They provide some convenience function to interact with the `Application` or the `Entity` itself.

## Build

This repository contains the source for the engine itself that gets compiled to a dynamic library and a little demo.
By default both are built but the demo can be disabled passing `-DCOMPILE_DEMO=OFF` to `cmake`.
Using `-G Ninja` is recommended for faster build times.

```sh
cmake -S . -B build
cmake --build build
```
