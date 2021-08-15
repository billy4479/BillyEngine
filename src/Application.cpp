#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hpp"

namespace BillyEngine {

Application::Application(std::string title, i32 width, i32 height)
    : m_Height(height),
      m_Width(width),
      m_Title(std::move(title)),
      m_AssetManager(this) {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error("SDL_image failed to initialize.");

    m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, 0);

#ifdef DEBUG
    if (m_Window == nullptr) dbg_print("%s\n", SDL_GetError());
#endif
    assert(m_Window != nullptr);

    m_Renderer.Init(m_Window);

    m_AssetManager.LoadFont(
        "JetBrains Mono Regular Nerd Font Complete Mono.ttf", "JetBrains Mono",
        32);
}

Application::~Application() {
    SDL_DestroyWindow(m_Window);
    m_AssetManager.ReleaseSDLModules();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::Run() {
    assert(!isRunning);
    isRunning = true;

    OnCreate();

    u32 frameStart = 0;
    i32 frameTime = 0;

    u32 lastDelta = 0;
    while (isRunning) {
        frameStart = SDL_GetTicks();
        m_Renderer.Clear();

        OnUpdate(lastDelta);
        m_Renderer.RenderToScreen();

        isRunning = !m_EventHandler.ShouldClose();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
            lastDelta = frameDelay;
        } else
            lastDelta = frameTime;
    }
}

void Application::AskToStop() { isRunning = false; }

void Application::OnCreate() {}

void Application::OnUpdate(f32 delta) {
    m_EventHandler.HandleEvents();

    m_EntityRegister.view<Components::ScriptComponent>().each(
        [&](auto entity, auto &script) {
            auto e = Entity(entity, &m_EntityRegister);
            if (!script.IsInstantiated()) {
                script.Instantiate(e);
                script.OnCreate(e);
            }
            script.OnUpdate(e, delta);
        });

    m_EntityRegister
        .view<Components::TextComponent, Components::TransformComponent>()
        .each([&](auto entity, auto &label, auto &t) {
            (void)entity;
            if (label.Texture == nullptr) {
                assert(label.Font != nullptr);
                label.Texture = m_Renderer.RenderTextToTexture(
                    label.Text, label.Font, label.fgColor);
            }
            m_Renderer.DrawTexture(label.Texture, t.Position, t.Scale,
                                   t.Rotation);
        });

    m_EntityRegister
        .view<Components::SpriteComponent, Components::TransformComponent>()
        .each([&](auto entity, auto &sprite, auto &t) {
            (void)entity;
            assert(sprite.Texture != nullptr);

            m_Renderer.DrawTexture(sprite.Texture, t.Position, t.Scale,
                                   t.Rotation);
        });
}

void Application::AddBasicComponets(Entity &e, const std::string &name) {
    e.AddComponent<Components::TagComponent>(name);
    e.AddComponent<Components::TransformComponent>();
}

Renderer *Application::GetRenderer() { return &m_Renderer; }

AssetManager *Application::GetAssetManager() { return &m_AssetManager; }

void Application::DestroyEntity(Entity entity) {
    m_EntityRegister.destroy(entity);
}

}  // namespace BillyEngine
