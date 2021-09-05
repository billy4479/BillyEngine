#include "TestEntity.hpp"

void TestEntity::OnCreate() {
    // dbg_print("%u\n", (u32) * this);
    texture = CreateScope<BillyEngine::DrawableTexture>(
        GetApplication()->CreateDrawableTexture({100, 100}));
    texture->Clear(BillyEngine::Color::hsl(hue, 0.5, 0.5));

    AddComponent<BillyEngine::Components::Sprite>(
        texture->FinalizeAndGetTexture());
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Position = {100, 100};
    t.Rotation = 0;
}

void TestEntity::OnUpdate(f64 delta) {
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Rotation += speed * delta;
    texture->Clear(BillyEngine::Color::hsl(hue, 0.5, 0.5));
    texture->Finalize();

    hue += u16(speed * delta);
    if (down)
        speed -= 1;
    else
        speed += 1;
    if (speed >= maxSpeed) down = true;
    if (speed <= -maxSpeed) down = false;
}
