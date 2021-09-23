#pragma once

#include "Event.hpp"
#include "KeyCodes.hpp"

namespace BillyEngine {

class KeyboardEvent : public Event {
   public:
    KeyboardEvent(Key::KeyCode keyCode, Key::Mods::Mods mods)
        : m_Key(keyCode), m_Mods(mods) {}
    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

    Key::KeyCode GetKeyCode() { return m_Key; }
    Key::Mods::Mods GetKeyMods() { return m_Mods; }

   protected:
    Key::KeyCode m_Key;
    Key::Mods::Mods m_Mods;
};

class KeyPressedEvent : public KeyboardEvent {
   public:
    KeyPressedEvent(const Key::KeyCode keycode, const Key::Mods::Mods mods)
        : KeyboardEvent(keycode, mods) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_Key;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyReleasedEvent : public KeyboardEvent {
   public:
    KeyReleasedEvent(const Key::KeyCode keycode, const Key::Mods::Mods mods)
        : KeyboardEvent(keycode, mods) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_Key;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

}  // namespace BillyEngine