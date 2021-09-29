#pragma once

#include <BillyEngine.hpp>

class TestEntity : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(TestEntity)
    Ref<BillyEngine::DrawableTexture> texture;
    f32 hue = 0;
    f32 speed = 10;
    static constexpr f32 maxSpeed = 300;
    bool down = false;
    bool paused = false;

    void OnCreate() override;
    void OnUpdate(f32 delta) override;
};