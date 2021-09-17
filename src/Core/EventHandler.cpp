#include "EventHandler.hpp"

namespace BillyEngine {
void EventHandler::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:

                m_ShouldClose = true;
                BE_CORE_INFO("Quitting...");
                break;
        }
    }
}

bool EventHandler::ShouldClose() { return m_ShouldClose; }
}  // namespace BillyEngine