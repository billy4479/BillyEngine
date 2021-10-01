#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/FPSManager.hpp"
#include "Core/Logger.hpp"
#include "Debugging/Assert.hpp"
#include "Debugging/Profiler.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityBehavior.hpp"
#include "Entity/EntityManager.hpp"
#include "Event/AppEvents.hpp"
#include "Event/EventManager.hpp"
#include "Event/Input.hpp"
#include "Rendering/DrawableTexture.hpp"
#include "Rendering/Renderer.hpp"
#include "Window/Window.hpp"

namespace BillyEngine {

Application* Application::s_Instance = nullptr;

Application::Application(const AppConfig& appConfig) {
    BE_PROFILE_FUNCTION();
    if (s_Instance != nullptr) BE_ABORT();
    s_Instance = this;

    Logger::Init();

#ifdef DEBUG
    BE_CORE_INFO("Running in debug mode");
#endif

    m_EventManager = Scope<EventManager>(new EventManager(this));
    m_Window = CreateScope<Window>(appConfig, this);
    m_AssetManager = CreateScope<AssetManager>(appConfig.AssetsPath);
    m_EntityManager = CreateScope<EntityManager>(this);
    m_Renderer = CreateScope<Renderer>(m_Window->m_Window);
    m_FPSManager = CreateScope<FPSManager>(appConfig.TargetFPS);

    Input::Bind(this);
}

Application::~Application() { s_Instance = nullptr; }

void Application::Run() {
    BE_PROFILE_FUNCTION();

    BE_ASSERT(!isRunning);
    isRunning = true;

    while (isRunning) {
        m_FPSManager->StartFrame();

        Frame(m_FPSManager->GetElapsed());

        m_FPSManager->EndFrameAndWait();
    }
    BE_CORE_INFO("Quitting...");
}

void Application::Stop() { isRunning = false; }

void Application::Frame(f32 delta) {
    BE_PROFILE_FUNCTION();

    m_Renderer->Clear();
    m_EventManager->HandleEvents();
    m_EventManager->FireEvent(BeforeScriptsEvent(delta));
    m_EntityManager->Update(delta);
    m_EventManager->FireEvent(AfterScriptsEvent(delta));
    m_Renderer->RenderToScreen();
}

// Proxies

Ref<DrawableTexture> Application::CreateDrawableTexture(glm::ivec2 size) {
    return CreateRef<DrawableTexture>(m_Renderer->CreateDrawableTexture(size));
}

Entity Application::CreateEntity(const std::string& name) {
    return m_EntityManager->CreateEntity(name);
}

void Application::DestroyEntity(Entity entity) {
    m_EntityManager->DestroyEntity(entity);
}

Entity Application::DuplicateEntity(Entity entity, std::string_view name) {
    auto e = m_EntityManager->Duplicate(entity);
    if (!name.empty()) {
        e.GetComponentM<Components::Tag>().Name = name;
    }
    return e;
}

void Application::SetAssetFolder(const std::filesystem::path& path) {
    m_AssetManager->SetAssetFolder(path);
}

std::filesystem::path Application::GetAssetFolder() {
    return m_AssetManager->GetAssetFolder();
}

Ref<Font> Application::LoadFont(const std::filesystem::path& path,
                                const std::string& name, u32 size) {
    return m_AssetManager->LoadFont(path, name, size);
}

Ref<Font> Application::GetFont(const std::string& name) {
    return m_AssetManager->GetFont(name);
}

Ref<Surface> Application::LoadImage(const std::filesystem::path& path,
                                    const std::string name) {
    return m_AssetManager->LoadImage(path, name);
}

Ref<Surface> Application::GetImage(const std::string& name) {
    return m_AssetManager->GetImage(name);
}

const glm::ivec2 Application::GetSize() const { return m_Window->GetSize(); }

void Application::SetTitle(std::string_view title) {
    m_Window->SetTitle(title);
}

void Application::SetResizable(bool resizable) {
    m_Window->SetResizable(resizable);
}

void Application::SetFullscreen(bool fullscreen) {
    m_Window->SetFullScreen(fullscreen);
}

bool Application::IsResizable() const { return m_Window->IsResizable(); }

bool Application::IsFullscreen() const { return m_Window->IsFullScreen(); }

bool Application::HasFocus() const { return m_Window->HasFocus(); }

void Application::GetFocus() { m_Window->GetFocus(); }

bool Application::IsBorderless() const { return m_Window->IsBorderless(); }

void Application::SetBorderless(bool borderless) {
    m_Window->SetBorderless(borderless);
}

f32 Application::GetFPS() const { return m_FPSManager->GetActualFPS(); }

f32 Application::GetTargetFPS() const { return m_FPSManager->GetTargetFPS(); }

void Application::SetTargetFPS(f32 fps) { m_FPSManager->SetTargetFPS(fps); }

u64 Application::GetFrameCount() const { return m_FPSManager->GetFrameCount(); }

bool Application::FireEvent(Event&& event) {
    return m_EventManager->FireEvent(std::move(event));
}

u32 Application::RegisterEventListener(std::function<bool(Event&)> listener) {
    return m_EventManager->RegisterListener(listener);
}

}  // namespace BillyEngine
