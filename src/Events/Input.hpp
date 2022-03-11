#pragma once

#include <glm/vec2.hpp>

#include "Keycodes.hpp"
#include "MouseCodes.hpp"

namespace BillyEngine {

class Window;

class Input {
   public:
    Input(Window&);
    ~Input();

    bool IsKeyPressed(KeyCode);
    bool IsMouseButtonPressed(MouseCode);

    glm::vec2 GetMousePosition();

   private:
    Window& m_Window;
};

}  // namespace BillyEngine