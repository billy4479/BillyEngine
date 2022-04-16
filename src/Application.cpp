#include "Application.hpp"

#include "Assets/AssetManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Types.hpp"
#include "Events/EventManager.hpp"
#include "Events/Input.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

Scope<Application> Application::s_Instance{nullptr};

Application::Application()
    : m_AssetManager(CreateScope<AssetManager>()),
      m_Window(CreateScope<Window>("BillyEngine", glm::ivec2{800, 600})),
      m_Renderer(CreateScope<Renderer>(*m_AssetManager)),
      m_EventManager(CreateScope<EventManager>(*m_Window)),
      m_Input(CreateScope<Input>(*m_Window)) {}

void Application::Run() {
    Logger::Core()->info("Started!");

    auto c = Color::FromU32(0x333333ff);
    m_Renderer->SetClearColor(c);
    // m_Renderer->SetWireframeView(true);

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
    if (!s_Instance) {
        Logger::Init();
        s_Instance = Scope<Application>(new Application());
    }

    return *s_Instance;
}

void Application::Reset() {
    if (!s_Instance) return;

    s_Instance = nullptr;
}

Application::~Application() { Logger::Core()->info("Cleaning up."); }

}  // namespace BillyEngine
