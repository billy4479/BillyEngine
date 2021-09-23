#include "TestEntity2.hpp"

void TestEntity2::OnCreate() {
    AddComponent<BillyEngine::Components::Text>("", App.GetFont("OpenSans"));
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Position = {App.GetSize().x - 10, 5};

    RegisterEventListener<BillyEngine::WindowResizeEvent>(
        [&](BillyEngine::WindowResizeEvent &) -> bool {
            GetComponent<BillyEngine::Components::Transform>().Position = {
                App.GetSize().x - 10, 5};
            return false;
        });

    t.Anchor = BillyEngine::CenterPoint::TOP_RIGHT;
}

void TestEntity2::OnUpdate(f32) {
    std::stringstream ss;
    ss << "FPS: " << App.GetFPS();

    GetComponent<BillyEngine::Components::Text>().SetText(ss.str());
}
