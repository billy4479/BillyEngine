# Billy Engine

[![Build Status](https://github.com/billy4479/BillyEngine/actions/workflows/build.yml/badge.svg)](https://github.com/billy4479/BillyEngine/actions/workflows/build.yml)

Some kind of 2D game engine, written in C++20 using OpenGL and EnTT to be used in future projects.
I wanted a simple entity framework to display some graphics in my C++ applications and here it is.
It is not meant to be like Unreal / Unity / Godot,
the most similar thing I could find is [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) and [raylib](https://github.com/raysan5/raylib). Thanks also to [TheCherno](https://www.youtube.com/c/TheChernoProject) for [Hazel](https://github.com/TheCherno/Hazel) from which I took a lot of inspiration.

I've developed it in Linux for Linux ~~but _should_ work on other platforms as well~~. Windows is WIP, OSX will probably not work.
I'm not targeting mobile.
WASM may be interesting but definitely not a priority.

There's still a lot of work to do, check out [TODO.md](TODO.md)

It started using SDL2 for rendering but switching to OpenGL gives more customization and advanced features.
Also, linking SDL2 on windows is a pain. 

## How to use

You can look at the code in the [demo folder](Demo) for now as there is no documentation
and the API is really unstable.

In the future I would like to provide a full C-compatible API
and some bindings using a easier language (maybe C#).

## Build

This repository contains the source for the engine itself that gets compiled to a dynamic library and a little demo.

```sh
cmake -S . -B build # `-G Ninja` is recommended but not required
cmake --build build
```

Some options that you can pass to `cmake` include:
 - `-D COMPILE_DEMO=OFF` to disable the demo
 - `-D BUNDLE_DEPENDENCIES=OFF` to get multiple DLLs for each dependency. By default they are bundled into a single DLL
 - `-D SYSTEM_DEPENDENCIES=ON` to build the engine using packages on the system instead of downloading and compiling them (some dependencies will still be compiled because they are non-standard and usually not packaged). This works well on Linux, in particular, on Arch you would need to `yay -S entt fmt glm glfw-x11 spdlog`. On the other side this option is not recommended on Windows
