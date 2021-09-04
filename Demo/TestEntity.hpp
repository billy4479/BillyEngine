#pragma once

#include <BillyEngine.hpp>

class TestEntity : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity)

    // FIXME: Here there some kind of undefined behaviour...

   public:
    Scope<BillyEngine::DrawableTexture> texture;
    f32 hue = 0;
    f32 speed = 100;
    const f32 maxSpeed = 1000;
    bool down = false;

    void OnCreate() override {
        // dbg_print("%u\n", (u32) * this);
        texture = CreateScope<BillyEngine::DrawableTexture>(
            m_Application->CreateDrawableTexture({100, 100}));
        texture->Clear(BillyEngine::Color::hsl(hue, 0.5, 0.5));

        AddComponent<BillyEngine::Components::Sprite>(
            texture->FinalizeAndGetTexture());
        auto &t = GetComponent<BillyEngine::Components::Transform>();
        t.Position = {100, 100};
        t.Rotation = 0;
    }
    void OnUpdate(f64 delta) override {
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

        m_Application->AskToStop();
    }
    void OnDestroy() override {}
};