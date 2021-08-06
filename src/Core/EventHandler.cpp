#include "EventHandler.hpp"

void EventHandler::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_ShouldClose = true;
                dbg_print("Quitting\n");
                break;
        }
    }
}

bool EventHandler::ShouldClose() { return m_ShouldClose; }