#include "Spawner.hpp"

#include "ColoredQuad.hpp"
#include "PrintName.hpp"

void Spawner::OnCreate() {
    auto &e1 = App().CreateEntityAndAddBehavior<ColoredQuad>("Quad 1");
    e1.AddComponent<PrintName>(e1);

    auto &e2 = App().DuplicateEntity(e1, "Quad 2").GetComponentM<ColoredQuad>();
    auto &e3 = App().DuplicateEntity(e1, "Quad 3").GetComponentM<ColoredQuad>();

    Log.Debug("Setting colors");
    e1.color = BillyEngine::Color::red;
    e2.color = BillyEngine::Color::blue;
    e3.color = BillyEngine::Color::green;

    e1.TransformM().Position = {100, 500};
    e2.TransformM().Position = {210, 500};
    e3.TransformM().Position = {320, 500};

    Destroy();
}
