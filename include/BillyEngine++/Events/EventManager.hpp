#pragma once

#include <functional>
#include <unordered_map>

#include "Core/Types.hpp"
#include "Events/Event.hpp"

namespace BillyEngine {

class Window;

class EventManager {
   public:
    EventManager(Window&);
    ~EventManager();

    void HandleEvents();

    template <typename T, typename F>
    u32 AddListener(F listener) {
        static_assert(std::is_base_of_v<Event, T>,
                      "EventType must derive from Event");

        m_Listeners[++m_NextID] = [listener](const Event& e) {
            if (e.GetEventType() != T::GetEventTypeS()) return;

            listener(static_cast<const T&>(e));
        };
        return m_NextID;
    }
    void RemoveListener(u32);

    void Dispatch(const Event&) const;

   private:
    std::unordered_map<u32, std::function<void(const Event&)>> m_Listeners;
    u32 m_NextID{0};
};

}  // namespace BillyEngine