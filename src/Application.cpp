#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/Logger.hpp"
#include "Debugging/Profiler.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Event/AppEvents.hpp"
#include "Event/Input.hpp"
#include "Rendering/DrawableTexture.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

Application::Application(std::string_view title, glm::ivec2 size,
                         bool resizable, bool fullscreen,
                         const std::filesystem::path& assetsPath)
    : m_EventHandler(this),
      m_Window(title, size, this),
      m_AssetManager(assetsPath),
      m_EntityManager(this),
      m_Renderer(m_Window.m_Window) {
    BE_PROFILE_FUNCTION();
    Logger::Init();
    Input::Bind(this);

    m_Window.SetResizable(resizable);
    m_Window.SetFullScreen(fullscreen);
}

Application::~Application() = default;

void Application::Run() {
    BE_PROFILE_FUNCTION();

    BE_ASSERT(!isRunning);
    isRunning = true;

    u32 lastDelta = 1;
    while (isRunning) {
        auto start = SDL_GetTicks();

        Frame((f32)lastDelta / 1000.0f);

        auto end = SDL_GetTicks();
        lastDelta = end - start;

        if (frameDelay > lastDelta) {
            SDL_Delay(frameDelay - lastDelta);
            lastDelta = frameDelay;
        }

        m_ActualFps = 1000.0f / (f32)lastDelta;
    }
}

void Application::AskToStop() {
    BE_CORE_INFO("Quitting...");
    isRunning = false;
}

void Application::Frame(f32 delta) {
    BE_PROFILE_FUNCTION();

    m_Renderer.Clear();
    m_EventHandler.HandleEvents();
    m_EventHandler.FireEvent(BeforeScriptsEvent(delta));
    m_EntityManager.Update(delta);
    m_EventHandler.FireEvent(AfterScriptsEvent(delta));
    m_Renderer.RenderToScreen();
}

Renderer* Application::GetRenderer() { return &m_Renderer; }

Ref<DrawableTexture> Application::CreateDrawableTexture(glm::ivec2 size) {
    return CreateRef<DrawableTexture>(m_Renderer.CreateDrawableTexture(size));
}

}  // namespace BillyEngine
