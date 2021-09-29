#pragma once

#include <BillyEngine.hpp>

class ColoredQuad : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(ColoredQuad)
    BillyEngine::Color color = BillyEngine::Color::white;

    void OnCreate() override;
    void OnUpdate(f32) override {}
};