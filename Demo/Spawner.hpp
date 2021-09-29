#include <BillyEngine.hpp>

#include "TestEntity3.hpp"

class Spawner : public BillyEngine::ScriptableEntity {
   public:
    SCRIPTABLE_ENTITY(Spawner)

    void OnCreate() {
        auto &e1 = App.CreateScriptableEntity<TestEntity3>("Quad 1");
        auto &e2 = App.CreateScriptableEntity<TestEntity3>("Quad 2");
        auto &e3 = App.CreateScriptableEntity<TestEntity3>("Quad 3");
        e1.color = BillyEngine::Color::red;
        e2.color = BillyEngine::Color::blue;
        e3.color = BillyEngine::Color::green;

        e1.Transform().Position = {100, 500};
        e2.Transform().Position = {210, 500};
        e3.Transform().Position = {320, 500};

        Destroy();
    }
};