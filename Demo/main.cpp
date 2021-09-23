#include <BillyEngine.hpp>

#include "TestEntity.hpp"
#include "TestEntity2.hpp"
#include "TestEntity3.hpp"

int main() {
    BillyEngine::Application app;
    app.SetAssetFolder("assets");
    app.LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);
    app.LoadFont("JetBrains Mono Regular Nerd Font Complete Mono.ttf",
                 "JetBrainsMono", 34);

    app.CreateScriptableEntity<TestEntity>();
    app.CreateScriptableEntity<TestEntity2>();
    auto& e1 = app.CreateScriptableEntity<TestEntity3>();
    auto& e2 = app.CreateScriptableEntity<TestEntity3>();
    auto& e3 = app.CreateScriptableEntity<TestEntity3>();
    e1.color = BillyEngine::Color::red;
    e2.color = BillyEngine::Color::blue;
    e3.color = BillyEngine::Color::green;

    e1.Transform().Position = {100, 500};
    e2.Transform().Position = {210, 500};
    e3.Transform().Position = {320, 500};

    auto e = app.CreateEntity();
    e.AddComponent<BillyEngine::Components::Text>("BillyEngine!",
                                                  app.GetFont("JetBrainsMono"));
    auto& t = e.GetComponent<BillyEngine::Components::Transform>();
    t.Position = app.GetSize() / 2;
    app.GetEventHandler()
        .RegisterListenerForEventType<BillyEngine::WindowResizeEvent>(
            [&](BillyEngine::WindowResizeEvent&) -> bool {
                t.Position = app.GetSize() / 2;
                return false;
            });

    t.Anchor = BillyEngine::CenterPoint::CENTER_CENTER;

    app.Run();

    return 0;
}
