#pragma once

#include <BillyEngine.hpp>

class TestEntity : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity)

   public:
    BillyEngine::DrawableTexture texture;
    u16 hue = 0;

    void OnCreate() override {
        texture =
            m_Application->GetRenderer()->CreateDrawableTexture({100, 100});
        texture.Clear(BillyEngine::Color::hsl(hue, 0.5, 0.5));

        AddComponent<BillyEngine::Components::Sprite>(
            texture.FinalizeAndGetTexture());
        GetComponent<BillyEngine::Components::Transform>().Position = {100,
                                                                       100};
    }
    void OnUpdate(f32) override {
        GetComponent<BillyEngine::Components::Transform>().Rotation += 1;
        texture.Clear(BillyEngine::Color::hsl(++hue, 0.5, 0.5));
        texture.Finalize();
    }
    void OnDestroy() override {}
};