#include "Application.hpp"

#include <SDL_timer.h>

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Rendering/DrawableTexture.hpp"

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

    u32 lastDelta;
    while (isRunning) {
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
        // dbg_print("FrameTime: %fs\n", (f64)lastDelta.count() / 1000000.0);

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

DrawableTexture Application::CreateDrawableTexture(glm::ivec2 size) {
    return m_Renderer->CreateDrawableTexture(size);
}

}  // namespace BillyEngine
