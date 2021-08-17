#include <BillyEngine.hpp>

#include "TestEntity.hpp"

int main() {
    BillyEngine::Application app("Test", 800, 600);
    auto am = app.GetAssetManager();
    am->SetAssetFolder("assets");
    am->LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);

    app.CreateScriptableEntity<TestEntity>("");
    app.Run();

    return 0;
}
