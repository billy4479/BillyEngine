# TODO

- [ ] Documentation :)
- [ ] C API

## Platform

Linux is the main platform, the other I will try to maintain build but that's it.

- [x] Linux
- [ ] Windows
- [ ] OSX
- [ ] WASM (?)

## Input class

- [x] Actually create it
- [x] Mouse events
- [x] Keyboard events
  - [ ] KeyTyped != KeyPressed

## Rendering

 - [ ] Different shapes
 - [ ] Vertex batching
 - [ ] Camera

## World

- [ ] Physics
  - [ ] Box2D (?)
  - [ ] Raycasting
  - [ ] Colliders
  - [ ] Rigidbody

## Entity

- [ ] Parent-children entities
- [x] UUIDs
- [ ] Entity duplication
- [ ] Behaviors in a C-friendly way
- [ ] Create some kind of EntityBlueprint/Prefab

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
