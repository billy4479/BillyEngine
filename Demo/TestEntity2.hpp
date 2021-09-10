#pragma once

#include <BillyEngine.hpp>

class TestEntity2 : public BillyEngine::ScriptableEntity {
    SCRIPTABLE_ENTITY(TestEntity2)

   public:
    void OnCreate();
    void OnUpdate(f32);
    void OnDestroy() {}
};