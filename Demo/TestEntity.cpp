#include "TestEntity.hpp"

void TestEntity::OnCreate() {
    texture = App().CreateDrawableTexture({100, 100});
    texture->Clear(BillyEngine::Color::white);
    texture->Finalize();

    AddComponent<BillyEngine::Components::Sprite>(texture);
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Position = {100, 100};
    t.Rotation = 0;
}

void TestEntity::OnUpdate(f32 delta) {
    if (BillyEngine::Input::KeyDown(BillyEngine::Key::Space)) paused = !paused;

    if (paused) return;

    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Rotation += speed * delta;
    GetComponent<BillyEngine::Components::Sprite>().Tint =
        BillyEngine::Color::hsl((u16)hue, 1, 0.5);

    hue += u16(speed * delta);
    if (down)
        speed -= 1;
    else
        speed += 1;
    if (speed >= maxSpeed) down = true;
    if (speed <= -maxSpeed) down = false;

    // Log.Debug("{}", t.Position);
}
