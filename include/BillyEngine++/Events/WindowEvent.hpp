#pragma once

#include "Events/Event.hpp"

namespace BillyEngine {

BE_CREATE_EVENT_CATEGORY_START(WindowEvent, Event)

struct WindowEventData {
    glm::ivec2 Position;
    glm::ivec2 Size;
    bool HasFocus;
};

WindowEventData Data{};

BE_CREATE_EVENT_CATEGORY_END();

BE_CREATE_EVENT(WindowCloseEvent, WindowEvent, WindowClose);
BE_CREATE_EVENT(WindowResizeEvent, WindowEvent, WindowResize);
BE_CREATE_EVENT(WindowMoveEvent, WindowEvent, WindowMoved);
BE_CREATE_EVENT(WindowFocusEvent, WindowEvent, WindowFocusChanged);

}  // namespace BillyEngine