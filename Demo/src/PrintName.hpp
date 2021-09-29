#pragma once

#include <BillyEngine.hpp>

class PrintName : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(PrintName)

    void OnCreate() override {
        Log.Debug("Heyy I'm new! My name is {}", Tag().Name);
    }

    void OnUpdate(f32) override {}
};