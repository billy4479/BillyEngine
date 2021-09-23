#pragma once

#include "Event.hpp"

namespace BillyEngine {
enum class MouseButton { Right, Left, Middle, Button4, Button5 };

class MouseEvent : public Event {
   public:
    MouseEvent(i32 x, i32 y) : x(x), y(y) {}

    EVENT_CLASS_CATEGORY(EventCategory::Mouse)

    i32 x, y;
};

class MouseButtonEvent : public MouseEvent {
   public:
    MouseButtonEvent(i32 x, i32 y, MouseButton button)
        : MouseEvent(x, y), Button(button) {}
    EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::MouseButton)

    MouseButton Button;
};

class MouseMovedEvent final : public MouseEvent {
   public:
    MouseMovedEvent(i32 x, i32 y) : MouseEvent(x, y) {}
    EVENT_CLASS_TYPE(MouseMoved)
};

class MouseScrolledEvent final : public MouseEvent {
   public:
    MouseScrolledEvent(i32 x, i32 y) : MouseEvent(x, y) {}
    EVENT_CLASS_TYPE(MouseScrolled)
};

class MouseButtonPressedEvent final : public MouseButtonEvent {
   public:
    MouseButtonPressedEvent(i32 x, i32 y, MouseButton button)
        : MouseButtonEvent(x, y, button) {}
    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent final : public MouseButtonEvent {
   public:
    MouseButtonReleasedEvent(i32 x, i32 y, MouseButton button)
        : MouseButtonEvent(x, y, button) {}
    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}  // namespace BillyEngine