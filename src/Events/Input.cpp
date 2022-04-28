#include "Events/Input.hpp"

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Rendering/Window.hpp"

namespace BillyEngine {
Input::Input(Window& window) : m_Window(window) {}

Input::~Input() {}

bool Input::IsKeyPressed(KeyCode key) {
    auto result = glfwGetKey(m_Window.m_Window, (i32)key);
    return result == GLFW_PRESS || result == GLFW_REPEAT;
}

glm::ivec2 Input::GetMousePosition() {
    f64 x, y;
    glfwGetCursorPos(m_Window.m_Window, &x, &y);
    return {x, y};
}

bool Input::IsMouseButtonPressed(MouseCode button) {
    return glfwGetMouseButton(m_Window.m_Window, (i32)button) == GLFW_PRESS;
}

}  // namespace BillyEngine