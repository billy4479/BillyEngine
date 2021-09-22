#pragma once

#include "../Core/Common.hpp"
#include "Event.hpp"
#include "KeyCodes.hpp"

namespace BillyEngine {
class Application;
class EventHandler {
   public:
    explicit EventHandler(Application*);

    void HandleEvents();

    void RegisterListener(std::function<bool(Event&)>);

   private:
    void OnEvent(Event&&);
    void GetEventObject(const SDL_Event&);

    std::vector<std::function<bool(Event&)>> m_Listeners;

    Application* m_Application;
};
}  // namespace BillyEngine