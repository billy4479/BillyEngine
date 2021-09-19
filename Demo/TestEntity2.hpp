#pragma once

#include <BillyEngine.hpp>

class TestEntity2 : public BillyEngine::ScriptableEntity {
   public:
    SCRIPTABLE_ENTITY(TestEntity2)

    void OnCreate();
    void OnUpdate(f32);
};