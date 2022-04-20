#include "Application.hpp"

#include "Assets/AssetManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Types.hpp"
#include "Events/EventManager.hpp"
#include "Events/Input.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/WindowEvent.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

Application* Application::s_Instance{nullptr};

Application::Application(const ApplicationProprieties& props)
    : m_AssetManager(CreateScope<AssetManager>()),
      m_Window(CreateScope<Window>(props.Title, props.Size)),
      m_Renderer(CreateScope<Renderer>(*m_AssetManager)),
      m_EventManager(CreateScope<EventManager>(*m_Window)),
      m_Input(CreateScope<Input>(*m_Window)) {
    m_Renderer->SetViewportSize(props.Size);
    m_EventManager->AddListener<WindowResizeEvent>(
        [&](const WindowResizeEvent& e) {
            m_Renderer->SetViewportSize(e.Data.Size);
            Logger::Core()->debug("Resize to {}:{}", e.Data.Size.x,
                                  e.Data.Size.x);
        });
}

void Application::Run() {
    Logger::Core()->info("Started!");

    // m_Renderer->SetWireframeView(true);
    m_EventManager->AddListener<MouseMovedEvent>([](const MouseEvent& e) {
        Logger::Core()->info("Mouse: {},{}", e.Data.Position.x,
                             e.Data.Position.y);
    });

    while (!m_Window->ShouldClose()) {
        m_EventManager->HandleEvents();
        m_Renderer->Render();
        m_Window->SwapBuffers();

        if (m_Input->IsKeyPressed(Keys::Escape)) Quit();
    }

    Logger::Core()->info("Stopped.");
}

void Application::Quit() { m_Window->SetShouldClose(true); }

Application& Application::The() {
    // We just die here since the logger might be uninitialized yet
    assert(s_Instance);

    return *s_Instance;
}

Application& Application::CreateOrReset(const ApplicationProprieties& props) {
    Logger::CreateOrReset();
    if (s_Instance) delete s_Instance;

    s_Instance = new Application(props);
    return *s_Instance;
}

Application::~Application() { Logger::Core()->info("Cleaning up."); }

}  // namespace BillyEngine
