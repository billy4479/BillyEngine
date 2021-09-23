#pragma once

#include "KeyCodes.hpp"

namespace BillyEngine {
class Application;
class Event;
class Input {
   public:
    /**
     * @brief Checks if the key was pressed and previously wasn't
     *
     * @return true if it was pressed
     * @return false if it wasn't
     */
    static bool KeyDown(Key::KeyCode, Key::Mods::Mods = Key::Mods::None);

    /**
     * @brief Checks if in this frame the key was released
     *
     * @return true if it was released
     * @return false if it wasn't
     */
    static bool KeyUp(Key::KeyCode, Key::Mods::Mods = Key::Mods::None);

    /**
     * @brief Checks if in this frame the key is pressed
     *
     * @return true if it is pressed
     * @return false if it isn't
     */
    static bool KeyPressed(Key::KeyCode, Key::Mods::Mods = Key::Mods::None);

   private:
    Input() = default;
    static void Bind(Application*);
    static bool EventHandler(Event&);

    static Application* s_Application;

    static std::set<Key::KeyCode> s_PressedKeys;
    static std::set<Key::KeyCode> s_PreviouslyPressedKeys;
    static Key::Mods::Mods s_Mods;

    static bool IsInPressedKeys(Key::KeyCode keyCode);
    static bool IsInPreviouslyPressedKeys(Key::KeyCode keyCode);
    static void Swap();

    friend class Application;
};

}  // namespace BillyEngine