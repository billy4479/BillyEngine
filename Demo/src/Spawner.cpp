#include "Spawner.hpp"

#include "ColoredQuad.hpp"
#include "PrintName.hpp"

void Spawner::OnCreate() {
    auto &e1 = App().CreateEntityAndAddBehavior<ColoredQuad>("Quad 1");
    auto &e2 = App().CreateEntityAndAddBehavior<ColoredQuad>("Quad 2");
    auto &e3 = App().CreateEntityAndAddBehavior<ColoredQuad>("Quad 3");

    e1.AddComponent<PrintName>(e1);
    e2.AddComponent<PrintName>(e2);
    e3.AddComponent<PrintName>(e3);

    e1.color = BillyEngine::Color::red;
    e2.color = BillyEngine::Color::blue;
    e3.color = BillyEngine::Color::green;

    e1.TransformM().Position = {100, 500};
    e2.TransformM().Position = {210, 500};
    e3.TransformM().Position = {320, 500};

    Destroy();
}
