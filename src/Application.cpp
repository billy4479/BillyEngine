#include "Application.hpp"

#include <SDL_timer.h>

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Rendering/DrawableTexture.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

Application::Application(std::string_view title, glm::ivec2 size,
                         const std::filesystem::path &assetsPath)
    : m_Window(title, size), m_AssetManager(assetsPath), m_EntityManager(this) {
    m_Window.m_DestructionCallback = [&]() {
        m_AssetManager.ReleaseSDLModules();
    };

    m_Renderer = CreateRef<Renderer>(m_Window.m_Window);
}

Application::~Application() = default;

void Application::Run() {
    BE_ASSERT(!isRunning);
    isRunning = true;

    u32 lastDelta = 1;
    while (isRunning) {
        // BE_PROFILE_SCOPE();

        auto start = SDL_GetTicks();

        m_Renderer->Clear();

        OnUpdate((f32)lastDelta / 1000.0f);

        isRunning = !m_EventHandler.ShouldClose();

        auto end = SDL_GetTicks();
        lastDelta = end - start;

        if (frameDelay > lastDelta) {
            SDL_Delay(frameDelay - lastDelta);
            lastDelta = frameDelay;
        }

        m_ActualFps = 1000.0 / lastDelta;
    }
}

void Application::AskToStop() { isRunning = false; }

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
