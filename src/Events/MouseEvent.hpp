#pragma once

#include <glm/vec2.hpp>

#include "Events/Event.hpp"
#include "Events/MouseCodes.hpp"

namespace BillyEngine {

BE_CREATE_EVENT_CATEGORY_START(MouseEvent, Event)

struct MouseEventData {
    MouseCode Button;
    glm::vec2 ScrollOffset;
    glm::ivec2 Position;
    i32 Mods;
};

MouseEventData Data{};

BE_CREATE_EVENT_CATEGORY_END();

BE_CREATE_EVENT(MouseButtonPressedEvent, MouseEvent, MouseButtonPressed);
BE_CREATE_EVENT(MouseButtonReleasedEvent, MouseEvent, MouseButtonReleased);
BE_CREATE_EVENT(MouseMovedEvent, MouseEvent, MouseMoved);
BE_CREATE_EVENT(MouseScrolledEvent, MouseEvent, MouseScrolled);

}  // namespace BillyEngine