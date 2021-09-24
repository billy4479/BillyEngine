#include <BillyEngine.hpp>

class TestEntity4 : public BillyEngine::ScriptableEntity {
   public:
    SCRIPTABLE_ENTITY(TestEntity4)

    void OnCreate() {
        auto t = App.CreateDrawableTexture({50, 50});
        t->Clear(BillyEngine::Color::white);
        t->Finalize();

        RegisterEventListener<BillyEngine::MouseButtonPressedEvent>(
            [t](auto& e) -> bool {
                switch (e.Button) {
                    case BillyEngine::MouseButton::Left:
                        t->Clear(BillyEngine::Color::green);
                        break;
                    case BillyEngine::MouseButton::Right:
                        t->Clear(BillyEngine::Color::red);
                        break;
                    case BillyEngine::MouseButton::Middle:
                        t->Clear(BillyEngine::Color::blue);
                        break;
                    default:
                        break;
                }
                t->Finalize();
                return true;
            });
        RegisterEventListener<BillyEngine::MouseButtonReleasedEvent>(
            [t](auto&) -> bool {
                t->Clear(BillyEngine::Color::white);
                t->Finalize();
                return true;
            });

        AddComponent<BillyEngine::Components::Sprite>(t);
        Transform().Anchor = BillyEngine::CenterPoint::CENTER_CENTER;
        Transform().zIndex = 1;
    }

    void OnUpdate(f32) {
        Transform().Position = BillyEngine::Input::GetMousePosition();
    }
};