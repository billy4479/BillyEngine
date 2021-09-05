#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hxx"
// #include "Entity/Entity.inl"
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

    std::chrono::microseconds lastDelta;
    while (isRunning) {
        auto start = std::chrono::high_resolution_clock::now();
        m_Renderer->Clear();

        OnUpdate((f64)lastDelta.count() / 1000000.0);

        isRunning = !m_EventHandler.ShouldClose();

        auto end = std::chrono::high_resolution_clock::now();
        lastDelta =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if (frameDelay > lastDelta) {
            SDL_Delay(std::chrono::duration_cast<std::chrono::milliseconds>(
                          frameDelay - lastDelta)
                          .count());
            lastDelta = frameDelay;
        }
        // dbg_print("FrameTime: %fs\n", (f64)lastDelta.count() / 1000000.0);

        m_ActualFps = 1000000.0 / lastDelta.count();
    }
}

void Application::AskToStop() { isRunning = false; }

void Application::OnUpdate(f64 delta) {
    m_EventHandler.HandleEvents();

    m_EntityManager.Update(delta);

    m_Renderer->RenderToScreen();
}

Ref<Renderer> Application::GetRenderer() { return m_Renderer; }

DrawableTexture Application::CreateDrawableTexture(glm::ivec2 size) {
    return m_Renderer->CreateDrawableTexture(size);
}

}  // namespace BillyEngine
