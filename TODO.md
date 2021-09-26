# TODO

- [ ] Documentation :)
- [x] Use the Application class more as a proxy to other classes which implement the actual functionality
- [x] Create a Window class to manage all the window related stuff abstracted away from SDL
- [x] Use a proper logger (maybe [spdlog](https://github.com/gabime/spdlog)?)
- [ ] Use `ccache` if available
- [ ] Move away from SDL libraries
  - [ ] Remove SDL_img
  - [ ] Remove SDL_ttf

## Platform

- [x] Linux
- [ ] Windows
- [ ] OSX
- [ ] WASM (?)

## Input class

- [x] Actually create it
- [x] Mouse events
- [x] Keyboard events

## Rendering

- [x] Use `SDL_Surface`s when needed and choose where to use those and where `SDL_Texture`s
- [x] Resizable window
- [x] Implement rendering tinted textures
- [ ] Draw shapes and primitives
  - [ ] Rectangle
  - [ ] Triangle
  - [ ] Circle
  - [ ] Line
- [ ] (OpenGL ?)

## Physics

- [ ] Box2D (?)
- [ ] Add physics class
  - [ ] Ray cast (?)
  - ... (?)
- [ ] Add physics components
  - [ ] BoxCollider
  - [ ] CircleCollider
  - [ ] PolygonCollider (?)
  - [ ] RigidBody

## Entity

- [ ] Parent-children entities
- [ ] UUIDs

## Audio

- [ ] Design
  - [ ] Figure out what a good architecture is, never worked with audio before :)
  - [ ] SDL or something else? (OpenAL?)
- [ ] Actual implementation

## Scene (?)

This has a question mark because it adds a notable complexity layer and might not be the right thing for such a small project.

- [ ] Be able to load in different scenes with different entities inside
- [ ] Scene serialization
  - [ ] Text based for development (JSON/YML)
  - [ ] Optimized loading for runtime ("compile" all text files at launch?)
- [ ] Project file (?)
