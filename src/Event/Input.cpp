#include "Input.hpp"

#include "../Application.hpp"
#include "Event.hpp"
#include "KeyboardEvent.hpp"

namespace BillyEngine {

Application* Input::s_Application = nullptr;
std::set<Key::KeyCode> Input::s_PressedKeys;
std::set<Key::KeyCode> Input::s_PreviouslyPressedKeys;
Key::Mods::Mods Input::s_Mods = Key::Mods::None;

// Current mods     = 0b00011110
// Wanted mods      = 0b00001110
// Current & Wanted = 0b00001110
// Check if AND result is equal to wanted

bool Input::KeyDown(Key::KeyCode keyCode, Key::Mods::Mods mods) {
    return ((s_Mods & mods) == mods && IsInPressedKeys(keyCode) &&
            !IsInPreviouslyPressedKeys(keyCode));
}

bool Input::KeyUp(Key::KeyCode keyCode, Key::Mods::Mods mods) {
    return ((s_Mods & mods) == mods && IsInPreviouslyPressedKeys(keyCode) &&
            !IsInPressedKeys(keyCode));
}

bool Input::KeyPressed(Key::KeyCode keyCode, Key::Mods::Mods mods) {
    return ((s_Mods & mods) == mods && IsInPressedKeys(keyCode));
}

glm::ivec2 Input::GetMousePosition() {
    glm::ivec2 result;
    SDL_GetMouseState(&result.x, &result.y);
    return result;
}

void Input::Bind(Application* application) {
    BE_ASSERT(application != nullptr);
    BE_ASSERT(s_Application == nullptr);
    s_Application = application;
    s_Application->GetEventHandler().RegisterListener(EventHandler);
    s_Application->GetEventHandler().RegisterBeforeUpdateHook(Swap);
}

bool Input::EventHandler(Event& e) {
    if ((e.GetEventCategory() & EventCategory::Input) != EventCategory::Input)
        return false;

    auto& kbEvent = dynamic_cast<KeyboardEvent&>(e);

    switch (kbEvent.GetEventType()) {
        case EventType::EventType::KeyPressed:
            s_PressedKeys.insert(kbEvent.GetKeyCode());
            s_Mods = kbEvent.GetKeyMods();
            return true;
        case EventType::EventType::KeyReleased:
            s_PressedKeys.erase(kbEvent.GetKeyCode());
            return true;

        default:
            return false;
    }
}

bool Input::IsInPressedKeys(Key::KeyCode keyCode) {
    return std::find(s_PressedKeys.begin(), s_PressedKeys.end(), keyCode) !=
           s_PressedKeys.end();
}

bool Input::IsInPreviouslyPressedKeys(Key::KeyCode keyCode) {
    return std::find(s_PreviouslyPressedKeys.begin(),
                     s_PreviouslyPressedKeys.end(),
                     keyCode) != s_PreviouslyPressedKeys.end();
}

void Input::Swap() { s_PreviouslyPressedKeys = s_PressedKeys; }
}  // namespace BillyEngine