#pragma once

#include "Event.hpp"

namespace BillyEngine {

class WindowEvent : public Event {
   public:
    EVENT_CLASS_CATEGORY(EventCategory::Window)
};

class WindowCloseEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowClose)
};

class WindowMovedEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowMoved)
    WindowMovedEvent(i32 x, i32 y) : x(x), y(y) {}
    i32 x, y;
};

class WindowResizeEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowResize)
    WindowResizeEvent(i32 x, i32 y) : x(x), y(y) {}
    i32 x, y;
};

class WindowFocusEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowFocus)
};

class WindowLostFocusEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowLostFocus)
};
}  // namespace BillyEngine