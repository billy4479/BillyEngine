#pragma once

#include <BillyEngine.hpp>

class TestEntity2 : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity2)

   public:
    void OnCreate() override {
        AddComponent<BillyEngine::Components::Text>(
            "", m_Application->GetFont("OpenSans"));
        auto &t = GetComponent<BillyEngine::Components::Transform>();
        t.Position = {m_Application->GetSize().x - 10, 5};
        t.Anchor = BillyEngine::CenterPoint::TOP_RIGHT;
    }
    void OnUpdate(f64) override {
        std::stringstream ss;
        ss << "FPS: " << m_Application->GetFPS();

        GetComponent<BillyEngine::Components::Text>().UpdateText(ss.str());
    }
    void OnDestroy() override {}
};