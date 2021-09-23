#pragma once

#include "Event.hpp"

namespace BillyEngine {

class AppEvent : public Event {
   public:
    EVENT_CLASS_CATEGORY(EventCategory::App)
    AppEvent(f32 delta) : Delta(delta) {}

    f32 Delta;
};

class BeforeScriptsEvent final : public AppEvent {
   public:
    EVENT_CLASS_TYPE(AppBeforeScripts)
    BeforeScriptsEvent(f32 delta) : AppEvent(delta) {}
};

class AfterScriptsEvent final : public AppEvent {
   public:
    EVENT_CLASS_TYPE(AppAfterScripts)
    AfterScriptsEvent(f32 delta) : AppEvent(delta) {}
};

}  // namespace BillyEngine