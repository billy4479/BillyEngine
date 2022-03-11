#include "EventManager.hpp"

#include <GLFW/glfw3.h>

#include "Rendering/Window.hpp"

namespace BillyEngine {

EventManager::EventManager(Window& window) : m_Window(window) {}

EventManager::~EventManager() {}

void EventManager::HandleEvents() { glfwPollEvents(); }

}  // namespace BillyEngine