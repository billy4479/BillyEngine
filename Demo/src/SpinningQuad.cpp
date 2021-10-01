#include "SpinningQuad.hpp"

void SpinningQuad::OnCreate() {
    auto texture = App().CreateDrawableTexture({100, 100});
    texture->Clear(BillyEngine::Color::white);

    GetComponentM<BillyEngine::Components::Sprite>().SetTexture(
        texture->FinalizeAndGetTexture());
    auto &t = TransformM();
    t.Position = {100, 100};
    t.Rotation = 0;
}

void SpinningQuad::OnUpdate(f32 delta) {
    if (BillyEngine::Input::KeyDown(BillyEngine::Key::Space)) paused = !paused;

    if (paused) return;

    TransformM().Rotation += speed * delta;
    GetComponentM<BillyEngine::Components::Sprite>().Tint =
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

void SpinningQuad::RegisterComponents() {
    AddComponent<BillyEngine::Components::Sprite>();
}
