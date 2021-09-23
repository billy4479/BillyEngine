#pragma once

#include <functional>

#include "../Core/Common.hpp"
#include "Event.hpp"
#include "KeyCodes.hpp"

namespace BillyEngine {
class Application;
class EventHandler {
   public:
    explicit EventHandler(Application*);

    void RegisterBeforeUpdateHook(std::function<void()>);
    bool FireEvent(Event&&);

    u32 RegisterListener(std::function<bool(Event&)>);
    void UnregisterListener(u32 id);

    template <typename T>
    u32 RegisterListenerForEventType(std::function<bool(T&)> listener) {
        static_assert(std::is_base_of<Event, T>::value,
                      "T must be derived from Event");
        return RegisterListener([listener](Event& e) -> bool {
            if (T::s_GetEventType() == e.GetEventType())
                return listener(dynamic_cast<T&>(e));
            return false;
        });
    }

   private:
    void HandleSDLEvent(const SDL_Event&);

    void HandleEvents();

    std::map<u32, std::function<bool(Event&)>> m_Listeners;
    std::vector<std::function<void()>> m_BeforeUpdateHooks;
    u32 m_NextListenerID = 0;

    Application* m_Application;
    friend Application;
};
}  // namespace BillyEngine