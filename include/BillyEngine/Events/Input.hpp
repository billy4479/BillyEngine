#pragma once

#include <glm/ext/vector_int2.hpp>

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

    glm::ivec2 GetMousePosition();

   private:
    Window& m_Window;
};

}  // namespace BillyEngine