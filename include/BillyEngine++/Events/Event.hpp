#pragma once

#include <glm/ext/vector_int2.hpp>

#include "Core/Types.hpp"

#define BE_CREATE_EVENT(name, base, type)                                   \
    class name final : public base {                                        \
       public:                                                              \
        EventType GetEventType() const override { return EventType::type; } \
        static EventType GetEventTypeS() { return EventType::type; }        \
    }

#define BE_CREATE_EVENT_CATEGORY_START(name, base) \
    class name : public base {                     \
       public:                                     \
        virtual EventType GetEventType() const override = 0;

#define BE_CREATE_EVENT_CATEGORY_END() }

namespace BillyEngine {

enum class EventType {
    WindowResize,
    WindowClose,
    WindowFocusChanged,
    WindowMoved,

    KeyPressed,
    KeyReleased,
    KeyTyped,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

class Event {
   public:
    virtual EventType GetEventType() const = 0;

    bool Handled{false};
};

}  // namespace BillyEngine