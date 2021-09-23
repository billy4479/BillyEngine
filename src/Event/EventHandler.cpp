#include "EventHandler.hpp"

#include <SDL_events.h>

#include "../Application.hpp"
#include "KeyboardEvent.hpp"
#include "WindowEvent.hpp"

namespace BillyEngine {
EventHandler::EventHandler(Application* application)
    : m_Application(application) {
    BE_ASSERT(m_Application != nullptr);

    RegisterListenerForEventType<CloseEvent>([this](CloseEvent&) -> bool {
        m_Application->AskToStop();
        return true;
    });
}

void EventHandler::GetEventObject(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            OnEvent(CloseEvent());
            break;

        case SDL_KEYUP:
            OnEvent(KeyReleasedEvent(event.key.keysym.scancode,
                                     event.key.keysym.mod));
            break;

        case SDL_KEYDOWN:
            OnEvent(KeyPressedEvent(event.key.keysym.scancode,
                                    event.key.keysym.mod));
            break;

        default:
            OnEvent(EventUnknown());
            break;
    }
}

void EventHandler::HandleEvents() {
    BE_PROFILE_FUNCTION();

    for (auto hook : m_BeforeUpdateHooks) hook();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        GetEventObject(event);
    }
}

void EventHandler::RegisterBeforeUpdateHook(std::function<void()> hook) {
    m_BeforeUpdateHooks.push_back(hook);
}

u32 EventHandler::RegisterListener(std::function<bool(Event&)> callback) {
    m_Listeners[m_NextListenerID] = callback;
    return ++m_NextListenerID;
}

void EventHandler::UnregisterListener(u32 id) { m_Listeners.erase(id); }

void EventHandler::OnEvent(Event&& e) {
    auto& event = e;

    for (auto listener : m_Listeners) {
        if (event.Handled) break;
        event.Handled = listener.second(event);
    }
}

}  // namespace BillyEngine