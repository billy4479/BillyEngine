#include <BillyEngine.hpp>

#include "TestEntity.hpp"

int main() {
    BillyEngine::Application app("Test", 1280, 720);
    auto am = app.GetAssetManager();
    am->SetAssetFolder("assets");
    am->LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);
    am->LoadFont("JetBrains Mono Regular Nerd Font Complete Mono.ttf",
                 "JetBrainsMono", 34);

    app.CreateScriptableEntity<TestEntity>("");

    auto e = app.CreateEntity("");
    e.AddComponent<BillyEngine::Components::TextComponent>(
        "Fixed Position", am->GetFont("JetBrainsMono"));
    auto& t = e.GetComponent<BillyEngine::Components::TransformComponent>();
    t.Position = app.GetSize() / 2;
    t.Anchor = BillyEngine::CenterPoint::CENTER_CENTER;

    app.Run();

    return 0;
}
