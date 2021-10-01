#include <BillyEngine.hpp>

class Spawner : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(Spawner)

    void OnCreate() override;
    void OnUpdate(f32) override {}
    void RegisterComponents() override {}
};