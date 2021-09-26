#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace EventType {
enum class EventType {
    Unknown = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppBeforeScripts,
    AppAfterScripts,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};
}

namespace EventCategory {
enum EventCategory : u8 {
    None = 0,
    Window = BE_BIT(7),
    Input = BE_BIT(6),
    Keyboard = BE_BIT(5),
    Mouse = BE_BIT(4),
    MouseButton = BE_BIT(3),
    App = BE_BIT(2),
};
}  // namespace EventCategory

class Event {
   public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType::EventType GetEventType() const = 0;
    virtual EventCategory::EventCategory GetEventCategory() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

#define EVENT_CLASS_TYPE(type)                                   \
    static EventType::EventType s_GetEventType() {               \
        return EventType::EventType::type;                       \
    }                                                            \
    virtual EventType::EventType GetEventType() const override { \
        return s_GetEventType();                                 \
    }                                                            \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                       \
    virtual EventCategory::EventCategory GetEventCategory() const override { \
        return EventCategory::EventCategory(static_cast<u8>(category));      \
    }

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.ToString();
}

class EventUnknown final : public Event {
   public:
    EVENT_CLASS_CATEGORY(EventCategory::None)
    EVENT_CLASS_TYPE(Unknown)
};

}  // namespace BillyEngine