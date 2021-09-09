#pragma once

#include <BillyEngine.hpp>

class TestEntity3 : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity3)
   public:
    BillyEngine::Color color = BillyEngine::Color::white;

    void OnCreate() override {
        auto dt = GetApplication()->CreateDrawableTexture({100, 100});
        dt->Clear(color);
        dbg_print("#%X\n", (u32)color);
        dt->Finalize();
        AddComponent<BillyEngine::Components::Sprite>(dt);
    }

    void OnUpdate(f32) override {}
    void OnDestroy() override {}
};