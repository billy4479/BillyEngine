# TODO

- [ ] Documentation :)

## Input class

- [ ] Actually create it
- [ ] Mouse events
- [ ] Keyboard events

## Rendering

- [x] Use `SDL_Surface`s when needed and choose where to use those and where `SDL_Texture`s
- [ ] Resizable window
- [ ] Draw shapes and primitives
  - [ ] Rectangle
  - [ ] Triangle
  - [ ] Circle
  - [ ] Line
- [ ] (OpenGL ?)

## Physics

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

## Scene (?)

This has a question mark because it adds a notable complexity layer and might not be the right thing for such a small project.

- [ ] Create the scene class
- [ ] Be able to load in different scenes with different entities inside
- [ ] Scene serialization
  - [ ] Text based for development (JSON/YML)
  - [ ] Optimized loading for runtime ("compile" all text files at launch?)
- [ ] Project file (?)
