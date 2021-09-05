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

    void OnCreate() override;
    void OnUpdate(f64 delta) override;
    void OnDestroy() override {}
};