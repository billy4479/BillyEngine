#include <BillyEngine.hpp>

class TestEntity4 : public BillyEngine::ScriptableEntity {
   public:
    SCRIPTABLE_ENTITY(TestEntity4)

    void OnCreate() {
        auto t = App.CreateDrawableTexture({50, 50});
        t->Clear(BillyEngine::Color::white);
        AddComponent<BillyEngine::Components::Sprite>(
            t->FinalizeAndGetTexture());

        App.RegisterEventListenerFor<BillyEngine::MouseButtonPressedEvent>(
            [this](auto& e) -> bool {
                switch (e.Button) {
                    case BillyEngine::MouseButton::Left:
                        GetComponent<BillyEngine::Components::Sprite>().Tint =
                            BillyEngine::Color::green;
                        break;
                    case BillyEngine::MouseButton::Right:
                        GetComponent<BillyEngine::Components::Sprite>().Tint =
                            BillyEngine::Color::red;
                        break;
                    case BillyEngine::MouseButton::Middle:
                        GetComponent<BillyEngine::Components::Sprite>().Tint =
                            BillyEngine::Color::blue;
                        break;
                    default:
                        break;
                }
                return true;
            });
        App.RegisterEventListenerFor<BillyEngine::MouseButtonReleasedEvent>(
            [this](auto&) -> bool {
                GetComponent<BillyEngine::Components::Sprite>().Tint =
                    BillyEngine::Color::white;
                return true;
            });

        Transform().Anchor = BillyEngine::CenterPoint::CENTER_CENTER;
        Transform().zIndex = 1;
    }

    void OnUpdate(f32) {
        Transform().Position = BillyEngine::Input::GetMousePosition();
    }
};