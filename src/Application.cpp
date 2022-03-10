#include "Application.hpp"

// We need this for the correct include order
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Core/Logger.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

void Application::Run() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        BE_CRITICAL("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        BE_CRITICAL("Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window,
                                   [](GLFWwindow*, i32 width, i32 height) {
                                       glViewport(0, 0, width, height);
                                   });

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Application::~Application() {
    BE_INFO("Quitting...");
    glfwTerminate();
}

}  // namespace BillyEngine

#include <BillyEngine/Application.h>

Application* CreateApplication() {
    return (Application*)new BillyEngine::Application();
}

void DestroyApplication(Application* app) {
    delete (BillyEngine::Application*)app;
}

void RunApplication(Application* app) {
    ((BillyEngine::Application*)app)->Run();
}
