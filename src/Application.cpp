#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/Logger.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Event/Input.hpp"
#include "Rendering/DrawableTexture.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

Application::Application(std::string_view title, glm::ivec2 size,
                         const std::filesystem::path &assetsPath)
    : m_Window(title, size),
      m_AssetManager(assetsPath),
      m_EventHandler(this),
      m_EntityManager(this) {
    BE_PROFILE_FUNCTION();
    Logger::Init();
    Input::Bind(this);

    m_Renderer = CreateRef<Renderer>(m_Window.m_Window);
}

Application::~Application() = default;

void Application::Run() {
    BE_PROFILE_FUNCTION();

    BE_ASSERT(!isRunning);
    isRunning = true;

    u32 lastDelta = 1;
    while (isRunning) {
        {
            BE_PROFILE_SCOPE("Frame");

            auto start = SDL_GetTicks();

            m_Renderer->Clear();

            OnUpdate((f32)lastDelta / 1000.0f);

            auto end = SDL_GetTicks();
            lastDelta = end - start;
        }

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

void Application::OnUpdate(f32 delta) {
    m_EventHandler.HandleEvents();

    m_EntityManager.Update(delta);

    m_Renderer->RenderToScreen();
}

Ref<Renderer> Application::GetRenderer() { return m_Renderer; }

Ref<DrawableTexture> Application::CreateDrawableTexture(glm::ivec2 size) {
    return CreateRef<DrawableTexture>(m_Renderer->CreateDrawableTexture(size));
}

}  // namespace BillyEngine
