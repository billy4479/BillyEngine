#include "EventManager.hpp"

#include "../Application.hpp"
#include "Event.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvents.hpp"
#include "WindowEvents.hpp"

namespace BillyEngine {
EventManager::EventManager(Application* application)
    : m_Application(application) {
    BE_ASSERT(m_Application != nullptr);

    RegisterListenerForEventType<WindowCloseEvent>(
        [this](WindowCloseEvent&) -> bool {
            m_Application->Stop();
            return true;
        });
}

constexpr static MouseButton ConvertMouseButton(u8 button) {
    switch (button) {
        case SDL_BUTTON_LEFT:
            return MouseButton::Left;
        case SDL_BUTTON_RIGHT:
            return MouseButton::Right;
        case SDL_BUTTON_MIDDLE:
            return MouseButton::Middle;
        case SDL_BUTTON_X1:
            return MouseButton::Button4;
        case SDL_BUTTON_X2:
            return MouseButton::Button5;
        default:
            BE_ABORT();
            return MouseButton::Right;
    }
}

void EventManager::HandleSDLEvent(const SDL_Event& event) {
    BE_PROFILE_FUNCTION();
    switch (event.type) {
        case SDL_QUIT:
            FireEvent(WindowCloseEvent());
            break;

        case SDL_KEYUP:
            FireEvent(KeyReleasedEvent((Key::KeyCode)event.key.keysym.scancode,
                                       event.key.keysym.mod));
            break;

        case SDL_KEYDOWN:
            FireEvent(KeyPressedEvent((Key::KeyCode)event.key.keysym.scancode,
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

        case SDL_MOUSEWHEEL:
            if (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
                FireEvent(MouseScrolledEvent(event.wheel.x, event.wheel.y));
            else
                FireEvent(
                    MouseScrolledEvent(event.wheel.x * -1, event.wheel.y * -1));
            break;

        case SDL_MOUSEBUTTONDOWN:
            FireEvent(MouseButtonPressedEvent(
                event.button.x, event.button.y,
                ConvertMouseButton(event.button.button)));
            break;
        case SDL_MOUSEBUTTONUP:
            FireEvent(MouseButtonReleasedEvent(
                event.button.x, event.button.y,
                ConvertMouseButton(event.button.button)));
            break;

        case SDL_MOUSEMOTION:
            FireEvent(MouseMovedEvent(event.motion.x, event.motion.y));
            break;

        default:
            FireEvent(EventUnknown());
            break;
    }
}

void EventManager::HandleEvents() {
    BE_PROFILE_FUNCTION();

    for (auto hook : m_BeforeUpdateHooks) hook();

    SDL_Event event;
    bool left = true;
    while (left) {
        {
            BE_PROFILE_SCOPE("Poll");
            left = SDL_PollEvent(&event);
        }
        HandleSDLEvent(event);
    }
}

void EventManager::RegisterBeforeUpdateHook(std::function<void()> hook) {
    m_BeforeUpdateHooks.push_back(hook);
}

u32 EventManager::RegisterListener(std::function<bool(Event&)> callback) {
    m_Listeners[m_NextListenerID] = callback;
    return ++m_NextListenerID;
}

void EventManager::UnregisterListener(u32 id) { m_Listeners.erase(id); }

bool EventManager::FireEvent(Event&& e) {
    auto& event = e;

    for (auto listener : m_Listeners) {
        if (event.Handled) break;
        event.Handled = listener.second(event);
    }
    return event.Handled;
}

}  // namespace BillyEngine