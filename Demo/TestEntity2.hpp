#pragma once

#include <BillyEngine.hpp>

class TestEntity2 : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity2)

   public:
    void OnCreate() override;
    void OnUpdate(f64) override;
    void OnDestroy() override {}
};