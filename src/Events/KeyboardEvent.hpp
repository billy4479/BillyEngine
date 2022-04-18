#pragma once

#include "Events/Event.hpp"
#include "Events/Keycodes.hpp"

namespace BillyEngine {

BE_CREATE_EVENT_CATEGORY_START(KeyboardEvent, Event)

struct KeyboardEventData {
    KeyCode Keycode;
    i32 Scancode;
    i32 Mods;
};

KeyboardEventData Data{};

BE_CREATE_EVENT_CATEGORY_END();

BE_CREATE_EVENT(KeyPressedEvent, KeyboardEvent, KeyPressed);
BE_CREATE_EVENT(KeyReleasedEvent, KeyboardEvent, KeyReleased);
BE_CREATE_EVENT(KeyTypedEvent, KeyboardEvent, KeyTyped);

}  // namespace BillyEngine