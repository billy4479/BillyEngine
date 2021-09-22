#pragma once

#include <ostream>

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace EventEnum {
enum class EventType {
    Unknown = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

enum EventCategory : u8 {
    None = 0,
    Window = BE_BIT(7),
    Input = BE_BIT(6),
    Keyboard = BE_BIT(5),
    Mouse = BE_BIT(4),
    MouseButton = BE_BIT(3),
};
}  // namespace EventEnum

class Event {
   public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventEnum::EventType GetEventType() const = 0;
    virtual EventEnum::EventCategory GetEventCategory() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

#define EVENT_CLASS_TYPE(type)                                   \
    virtual EventEnum::EventType GetEventType() const override { \
        return EventEnum::EventType::type;                       \
    }                                                            \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                   \
    virtual EventEnum::EventCategory GetEventCategory() const override { \
        return EventEnum::EventCategory(static_cast<u8>(category));      \
    }

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.ToString();
}

class EventUnknown final : public Event {
   public:
    EVENT_CLASS_CATEGORY(EventEnum::None)
    EVENT_CLASS_TYPE(Unknown)
};

}  // namespace BillyEngine