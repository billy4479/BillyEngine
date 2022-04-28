#include "Rendering/Window.hpp"

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

    BE_LOG_GL_CALL("glfwCreateWindow({}, {}, {}, nullptr, nullptr)", size.x,
                   size.y, title);
    m_Window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
    if (m_Window == nullptr) {
        Logger::Core()->critical("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    BE_LOG_GL_CALL("glfwMakeContextCurrent({})", (void*)m_Window);
    glfwMakeContextCurrent(m_Window);

    BE_LOG_GL_CALL("gladLoadGL({})", (void*)glfwGetProcAddress);
    if (!gladLoadGL(glfwGetProcAddress)) {
        Logger::Core()->critical("Failed to initialize GLAD");
        return;
    }
}

Window::~Window() {
    BE_LOG_GL_CALL("glfwTerminate()");
    glfwTerminate();
}

void Window::SwapBuffers() {
    BE_LOG_GL_CALL("glfwSwapBuffers({})", (void*)m_Window);
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() { return glfwWindowShouldClose(m_Window); }

void Window::SetShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(m_Window, shouldClose);
}

}  // namespace BillyEngine