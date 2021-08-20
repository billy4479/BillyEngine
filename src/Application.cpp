#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"

namespace BillyEngine {

Application::Application(const std::string &title, glm::ivec2 size)
    : m_Size(size), m_Title(std::move(title)), m_AssetManager(this) {
#ifdef DEBUG
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
#endif

    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error("SDL_image failed to initialize.");

    m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_Size.x, m_Size.y, 0);

#ifdef DEBUG
    if (m_Window == nullptr) dbg_print("%s\n", SDL_GetError());
#endif
    assert(m_Window != nullptr);

    m_Renderer.Init(m_Window);
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

    m_EntityRegister.view<Components::Script>().each(
        [&](auto entity, auto &script) {
            (void)entity;
            // auto e = Entity(entity, this);
            if (script.Instance == nullptr) {
                script.Instantiate();
                script.OnCreate(script.Instance);
            }
            script.OnUpdate(script.Instance, delta);
        });

    m_EntityRegister.view<Components::Text, Components::Transform>().each(
        [&](auto entity, auto &label, auto &t) {
            (void)entity;
            if (label.Texture == nullptr) {
                assert(label.Font != nullptr);
                label.Texture = m_Renderer.RenderTextToTexture(
                    label.Content, label.Font, label.fgColor);
            }
            m_Renderer.DrawTexture(label.Texture, t.Position, t.Scale,
                                   t.Rotation, t.Anchor, t.RotationCenter);
        });

    m_EntityRegister.view<Components::Sprite, Components::Transform>().each(
        [&](auto entity, auto &sprite, auto &t) {
            (void)entity;
#ifdef DEBUG
            if (sprite.GetTexture() != nullptr)
#endif
                m_Renderer.DrawTexture(sprite.GetTexture(), t.Position, t.Scale,
                                       t.Rotation, t.Anchor, t.RotationCenter);
#ifdef DEBUG
            else
                dbg_print("Not drawing since the texture is null\n");
#endif
        });
}

Entity Application::CreateEntity(const std::string &name) {
    Entity e = {m_EntityRegister.create(), this};

    std::string n;
    if (name.empty()) {
        std::stringstream ss;
        ss << "Entity [" << (u32)e << "]";
        ss >> n;
    } else {
        n = name;
    }

    e.AddComponent<Components::Tag>(name);
    e.AddComponent<Components::Transform>();

    return e;
}

Renderer *Application::GetRenderer() { return &m_Renderer; }

AssetManager *Application::GetAssetManager() { return &m_AssetManager; }

void Application::DestroyEntity(Entity entity) {
    m_EntityRegister.destroy(entity);
}

}  // namespace BillyEngine
