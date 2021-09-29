#include <BillyEngine.hpp>

class Spawner : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(Spawner)

    void OnCreate() override;
};