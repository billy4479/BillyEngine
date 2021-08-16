#pragma once

#include <BillyEngine.hpp>

class TestEntity : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity)

   public:
    void OnCreate() override {
        // FIXME:
        //! For some reason `this` contains messed up memory that points nowhere
        dbg_print("OnCreate [%d]\n", (u32)(*this));
        auto am = m_Application->GetAssetManager();
        AddComponent<BillyEngine::Components::TextComponent>(
            "Hey!", am->GetFont("OpenSans"));
    }
    void OnUpdate(f32) override {
        GetComponent<BillyEngine::Components::TransformComponent>()
            .Position.first += 1;
        // auto& t =
        // GetComponent<BillyEngine::Components::TransformComponent>();
        // t.Position = {t.Position.first + 1, t.Position.second};
    }
    void OnDestroy() override {}
};