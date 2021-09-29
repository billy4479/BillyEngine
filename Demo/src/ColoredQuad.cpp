#include "ColoredQuad.hpp"

void ColoredQuad::OnCreate() {
    Log.Debug("Created {} with color {}", Tag().Name, color);
    auto dt = App().CreateDrawableTexture({100, 100});
    dt->Clear(BillyEngine::Color::white);
    dt->Finalize();
    AddComponent<BillyEngine::Components::Sprite>(dt, color);
}
