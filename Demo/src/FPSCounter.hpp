#pragma once

#include <BillyEngine.hpp>

class FPSCounter : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(FPSCounter)

    void OnCreate() override;
    void OnUpdate(f32) override;
    void RegisterComponents() override;
};