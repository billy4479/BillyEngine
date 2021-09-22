#include "EventHandler.hpp"

#include "../Application.hpp"
#include "KeyboardEvent.hpp"
#include "WindowEvent.hpp"

namespace BillyEngine {
EventHandler::EventHandler(Application* application)
    : m_Application(application) {
    BE_ASSERT(m_Application != nullptr);

    RegisterListener([this](Event& e) -> bool {
        if (e.GetEventType() == EventEnum::EventType::WindowClose) {
            m_Application->AskToStop();
            return true;
        }
        if (e.GetEventType() != EventEnum::EventType::Unknown)
            BE_CORE_INFO(e.ToString());
        return false;
    });
}

void EventHandler::GetEventObject(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            OnEvent(CloseEvent());
            break;

        case SDL_KEYDOWN:
            OnEvent(KeyReleasedEvent(event.key.keysym.scancode,
                                     event.key.keysym.mod));
            break;

        case SDL_KEYUP:
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

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        GetEventObject(event);
    }
}

void EventHandler::RegisterListener(std::function<bool(Event&)> callback) {
    m_Listeners.push_back(callback);
}

void EventHandler::OnEvent(Event&& e) {
    auto& event = e;

    for (auto listener : m_Listeners) {
        if (event.Handled) break;
        event.Handled = listener(event);
    }
}

}  // namespace BillyEngine