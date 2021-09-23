#include "EventHandler.hpp"

#include <SDL_events.h>
#include <SDL_video.h>

#include "../Application.hpp"
#include "Event.hpp"
#include "KeyboardEvent.hpp"
#include "WindowEvent.hpp"

namespace BillyEngine {
EventHandler::EventHandler(Application* application)
    : m_Application(application) {
    BE_ASSERT(m_Application != nullptr);

    RegisterListenerForEventType<WindowCloseEvent>(
        [this](WindowCloseEvent&) -> bool {
            m_Application->AskToStop();
            return true;
        });
}

void EventHandler::HandleSDLEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            FireEvent(WindowCloseEvent());
            break;

        case SDL_KEYUP:
            FireEvent(KeyReleasedEvent(event.key.keysym.scancode,
                                       event.key.keysym.mod));
            break;

        case SDL_KEYDOWN:
            FireEvent(KeyPressedEvent(event.key.keysym.scancode,
                                      event.key.keysym.mod));
            break;

        case SDL_WINDOWEVENT: {
            switch (event.window.event) {
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_NONE:
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    FireEvent(WindowMovedEvent(event.window.data1,
                                               event.window.data2));
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    FireEvent(WindowResizeEvent(event.window.data1,
                                                event.window.data2));
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED: {
                    i32 w, h;
                    SDL_GetWindowSize(
                        SDL_GetWindowFromID(event.window.windowID), &w, &h);
                    FireEvent(WindowResizeEvent(w, h));
                } break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    FireEvent(WindowFocusEvent());
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    FireEvent(WindowLostFocusEvent());
                    break;
                default:
                    FireEvent(EventUnknown());
                    break;
            }

        } break;

        default:
            FireEvent(EventUnknown());
            break;
    }
}

void EventHandler::HandleEvents() {
    BE_PROFILE_FUNCTION();

    for (auto hook : m_BeforeUpdateHooks) hook();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        HandleSDLEvent(event);
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

bool EventHandler::FireEvent(Event&& e) {
    auto& event = e;

    for (auto listener : m_Listeners) {
        if (event.Handled) break;
        event.Handled = listener.second(event);
    }
    return event.Handled;
}

}  // namespace BillyEngine