#pragma once

#include <BillyEngine.hpp>

class TestEntity2 : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(TestEntity2)

    void OnCreate() override;
    void OnUpdate(f32) override;
};