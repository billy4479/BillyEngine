#include "Components/TextComponent.hpp"
#define SDL_MAIN_HANDLED
#include "Application.hpp"

int main() {
#ifdef DEBUG
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
#endif

    BillyEngine::Application app("Test", 800, 600);
    auto am = app.GetAssetManager();

    auto e = app.CreateEntity("Test :)");
    e.AddComponent<BillyEngine::Components::TextComponent>(
        "Hey!!", am->GetFont("JetBrains Mono"));

    app.Run();

    return 0;
}
