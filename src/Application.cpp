#include "Application.hpp"

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Component.hpp"

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

    if (m_Window == nullptr)
        std::runtime_error("SDL failed to create a window.");

    m_Renderer.Init(m_Window, m_Width, m_Height);
    m_AssetManager.LoadFont(
        "JetBrains Mono Regular Nerd Font Complete Mono.ttf", "JetBrains Mono",
        32);
}

Application::~Application() {
    SDL_DestroyWindow(m_Window);
    m_AssetManager.ReleaseSDLModules();
    TTF_Quit();
    SDL_Quit();
}

void Application::Run() {
    assert(!isRunning);
    isRunning = true;

    auto bg = Color(41, 41, 41);
    m_Renderer.Clear(bg);

    u32 frameStart;
    i32 frameTime;

    {
        auto e = CreateEntity("");
        e.AddComponent<Entity::TextComponent>(
            "Test", m_AssetManager.GetFont("JetBrains Mono"), Color::white);
    }
    u32 lastDelta = 0;
    while (isRunning) {
        frameStart = SDL_GetTicks();

        m_EventHandler.HandleEvents();

        auto reg = m_EntityRegister.GetReg();
        for (auto p : reg) {
            auto e = p.first;
            if (e.HasComponent<Entity::ScriptComponent>()) {
                e.GetComponent<Entity::ScriptComponent>().OnUpdate(lastDelta);
            }

            auto &transform = e.GetComponent<Entity::TransformComponent>();

            if (e.HasComponent<Entity::TextComponent>()) {
                auto &textComponent = e.GetComponent<Entity::TextComponent>();
                if (textComponent.Texture == nullptr) {
                    assert(textComponent.Font != nullptr);
                    textComponent.Texture = m_Renderer.RenderTextToTexture(
                        textComponent.Text, textComponent.Font,
                        textComponent.fgColor);
                }
                m_Renderer.DrawTexture(textComponent.Texture,
                                       transform.Position, transform.Scale,
                                       transform.Rotation);
            }

            if (e.HasComponent<Entity::SpriteComponent>()) {
                auto &sprite = e.GetComponent<Entity::SpriteComponent>();
                assert(sprite.Texture != nullptr);
                m_Renderer.DrawTexture(sprite.Texture, transform.Position,
                                       transform.Scale, transform.Rotation);
            }
        }

        m_Renderer.DrawToScreen();

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

Rendering::Renderer *Application::GetRenderer() { return &m_Renderer; }

AssetManager *Application::GetAssetManager() { return &m_AssetManager; }

Entity::Entity Application::CreateEntity(const std::string &name) {
    auto e = m_EntityRegister.CreateEntity();
    e.AddComponent<Entity::TagComponent>(name.empty() ? "Entity" : name);
    e.AddComponent<Entity::TransformComponent>();
    return e;
}
