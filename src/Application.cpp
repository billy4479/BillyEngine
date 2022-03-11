#include "Application.hpp"

#include "Core/Logger.hpp"
#include "Core/Types.hpp"
#include "Events/EventManager.hpp"
#include "Events/Input.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

Application::Application()
    : m_Window(CreateScope<Window>("BillyEngine", glm::ivec2{800, 600})),
      m_Renderer(),
      m_EventManager(CreateScope<EventManager>(*m_Window)),
      m_Input(CreateScope<Input>(*m_Window)) {
    Logger::Init();
}

void Application::Run() {
    Logger::Core()->info("Started!");

    while (!m_Window->ShouldClose()) {
        m_EventManager->HandleEvents();
        m_Renderer->Render();
        m_Window->SwapBuffers();

        if (m_Input->IsKeyPressed(Keys::Escape)) Quit();
    }

    Logger::Core()->info("Stopped.");
}

void Application::Quit() { m_Window->SetShouldClose(true); }

Application::~Application() { Logger::Core()->info("Quitting..."); }

}  // namespace BillyEngine
