#include <BillyEngine.hpp>

class MouseChaser : public BillyEngine::EntityBehavior {
   public:
    SCRIPTABLE_ENTITY(MouseChaser)

    void OnCreate() override;
    void OnUpdate(f32) override;
};