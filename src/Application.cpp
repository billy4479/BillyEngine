#include "Application.hpp"

#include "Core/Logger.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

Application::Application()
    : m_Window("BillyEngine", {800, 600}),
      m_Renderer(),
      m_EventManager(m_Window) {
    Logger::Init();
}

void Application::Run() {
    m_Running = true;
    Logger::Core()->info("Started!");

    while (m_Running) {
        m_EventManager.HandleEvents();
        m_Renderer.Render();
        m_Window.SwapBuffers();

        if (m_Running) m_Running = !m_Window.ShouldClose();
    }

    Logger::Core()->info("Stopped.");
}

void Application::Quit() { m_Running = false; }

Application::~Application() { Logger::Core()->info("Quitting..."); }

}  // namespace BillyEngine
