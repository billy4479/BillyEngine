#include <BillyEngine.hpp>

#include "FPSCounter.hpp"
#include "MouseChaser.hpp"
#include "Spawner.hpp"
#include "SpinningQuad.hpp"

int main() {
    BillyEngine::AppConfig appConfig;
    appConfig.Maximized = true;
    appConfig.AssetsPath = "assets";
    BillyEngine::Application app(appConfig);
    app.LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);
    app.LoadFont("JetBrains Mono Regular Nerd Font Complete Mono.ttf",
                 "JetBrainsMono", 34);

    app.CreateEntityAndAddBehavior<SpinningQuad>();
    app.CreateEntityAndAddBehavior<FPSCounter>();
    app.CreateEntityAndAddBehavior<MouseChaser>();
    app.CreateEntityAndAddBehavior<Spawner>();

    {
        auto e = app.CreateEntity();
        e.AddComponent<BillyEngine::Components::Text>(
            "BillyEngine!", app.GetFont("JetBrainsMono"));
        auto& t = e.GetComponentM<BillyEngine::Components::Transform>();
        t.Position = app.GetSize() / 2;
        app.RegisterEventListenerFor<BillyEngine::WindowResizeEvent>(
            [&e, &app](BillyEngine::WindowResizeEvent&) -> bool {
                auto& t = e.GetComponentM<BillyEngine::Components::Transform>();
                t.Position = app.GetSize() / 2;
                return false;
            });

        t.Anchor = BillyEngine::CenterPoint::CENTER_CENTER;
    }

    app.Run();

    return 0;
}
