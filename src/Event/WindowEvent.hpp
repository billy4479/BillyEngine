#pragma once

#include "Event.hpp"

namespace BillyEngine {

class WindowEvent : public Event {
   public:
    EVENT_CLASS_CATEGORY(EventEnum::Window)
};

class CloseEvent final : public WindowEvent {
   public:
    EVENT_CLASS_TYPE(WindowClose)
};
}  // namespace BillyEngine