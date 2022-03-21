#include "Window.hpp"

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Core/Logger.hpp"

namespace BillyEngine {
Window::Window(std::string_view title, glm::ivec2 size) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
    if (m_Window == nullptr) {
        Logger::Core()->critical("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        Logger::Core()->critical("Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(
        m_Window, [](GLFWwindow*, i32 width, i32 height) {
            glViewport(0, 0, width, height);
            Logger::Core()->debug("Resize to {}:{}", width, height);
        });
}

Window::~Window() { glfwTerminate(); }

void Window::SwapBuffers() { glfwSwapBuffers(m_Window); }

bool Window::ShouldClose() { return glfwWindowShouldClose(m_Window); }

void Window::SetShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(m_Window, shouldClose);
}

}  // namespace BillyEngine