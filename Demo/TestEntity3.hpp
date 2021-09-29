#pragma once

#include <BillyEngine.hpp>

class TestEntity3 : public BillyEngine::ScriptableEntity {
   public:
    SCRIPTABLE_ENTITY(TestEntity3)
    BillyEngine::Color color = BillyEngine::Color::white;

    void OnCreate() {
        Log.Debug("Created {} with color {}", Tag().Name, color);
        auto dt = App.CreateDrawableTexture({100, 100});
        dt->Clear(BillyEngine::Color::white);
        dt->Finalize();
        AddComponent<BillyEngine::Components::Sprite>(dt, color);
    }
};