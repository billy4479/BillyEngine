#pragma once

#include <BillyEngine.hpp>

class TestEntity : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity)

   public:
    Ref<BillyEngine::DrawableTexture> texture;
    f32 hue = 0;
    f32 speed = 10;
    const f32 maxSpeed = 300;
    bool down = false;

    void OnCreate() override;
    void OnUpdate(f32 delta) override;
    void OnDestroy() override {}
};