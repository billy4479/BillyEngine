#include "TestEntity2.hpp"

void TestEntity2::OnCreate() {
    AddComponent<BillyEngine::Components::Text>(
        "", GetApplication()->GetFont("OpenSans"));
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Position = {GetApplication()->GetSize().x - 10, 5};
    t.Anchor = BillyEngine::CenterPoint::TOP_RIGHT;
}

void TestEntity2::OnUpdate(f32) {
    std::stringstream ss;
    ss << "FPS: " << GetApplication()->GetFPS();

    GetComponent<BillyEngine::Components::Text>().SetText(ss.str());
}
