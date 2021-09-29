#include <BillyEngine.hpp>

#include "Spawner.hpp"
#include "TestEntity.hpp"
#include "TestEntity2.hpp"
#include "TestEntity3.hpp"
#include "TestEntity4.hpp"

int main() {
    BillyEngine::AppConfig appConfig;
    appConfig.Maximized = true;
    appConfig.AssetsPath = "assets";
    BillyEngine::Application app(appConfig);
    app.LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);
    app.LoadFont("JetBrains Mono Regular Nerd Font Complete Mono.ttf",
                 "JetBrainsMono", 34);

    app.CreateEntityAndAddBehavior<TestEntity>();
    app.CreateEntityAndAddBehavior<TestEntity2>();
    app.CreateEntityAndAddBehavior<TestEntity4>();
    app.CreateEntityAndAddBehavior<Spawner>();

    auto e = app.CreateEntity();
    e.AddComponent<BillyEngine::Components::Text>("BillyEngine!",
                                                  app.GetFont("JetBrainsMono"));
    auto& t = e.GetComponent<BillyEngine::Components::Transform>();
    t.Position = app.GetSize() / 2;
    app.RegisterEventListenerFor<BillyEngine::WindowResizeEvent>(
        [&e, &app](BillyEngine::WindowResizeEvent&) -> bool {
            auto& t = e.GetComponent<BillyEngine::Components::Transform>();
            t.Position = app.GetSize() / 2;
            return false;
        });

    t.Anchor = BillyEngine::CenterPoint::CENTER_CENTER;

    app.Run();

    return 0;
}
