#include "MouseChaser.hpp"

void MouseChaser::OnCreate() {
    auto t = App().CreateDrawableTexture({50, 50});
    t->Clear(BillyEngine::Color::white);
    GetComponentM<BillyEngine::Components::Sprite>().SetTexture(
        t->FinalizeAndGetTexture());

    App().RegisterEventListenerFor<BillyEngine::MouseButtonPressedEvent>(
        [this](auto& e) -> bool {
            switch (e.Button) {
                case BillyEngine::MouseButton::Left:
                    GetComponentM<BillyEngine::Components::Sprite>().Tint =
                        BillyEngine::Color::green;
                    break;
                case BillyEngine::MouseButton::Right:
                    GetComponentM<BillyEngine::Components::Sprite>().Tint =
                        BillyEngine::Color::red;
                    break;
                case BillyEngine::MouseButton::Middle:
                    GetComponentM<BillyEngine::Components::Sprite>().Tint =
                        BillyEngine::Color::blue;
                    break;
                default:
                    break;
            }
            return true;
        });
    App().RegisterEventListenerFor<BillyEngine::MouseButtonReleasedEvent>(
        [this](auto&) -> bool {
            GetComponentM<BillyEngine::Components::Sprite>().Tint =
                BillyEngine::Color::white;
            return true;
        });

    TransformM().Anchor = BillyEngine::CenterPoint::CENTER_CENTER;
    TransformM().zIndex = 1;
}
void MouseChaser::OnUpdate(f32) {
    TransformM().Position = BillyEngine::Input::GetMousePosition();
}

void MouseChaser::RegisterComponents() {
    AddComponent<BillyEngine::Components::Sprite>();
}
