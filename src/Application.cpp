#include "Application.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Component.hpp"
#include "Entity/Entity.hpp"

Application::Application(std::string title, i32 width, i32 height)
    : m_Height(height),
      m_Width(width),
      m_Title(std::move(title)),
      m_AssetManager(this) {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
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

    m_Renderer.Clear(Color(41, 41, 41));

    u32 frameStart;
    i32 frameTime;

    i32 count = 0;
    i32 line = 0;

    u16 h = 0;
    auto fg = Color(0, 153, 0);

    Entity::Entity e("test");
    e.AddComponent<Entity::TextComponent>("Test");

    while (isRunning) {
        frameStart = SDL_GetTicks();

        m_EventHandler.HandleEvents();

        // Logic here

        m_Renderer.Clear(Color::hsl(h++, 0.5, 0.5));

        // End of logic

        m_Renderer.Draw();

        isRunning = !m_EventHandler.ShouldClose();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
}

void Application::AskToStop() { isRunning = false; }

Rendering::Renderer *Application::GetRenderer() { return &m_Renderer; }

AssetManager *Application::GetAssetManager() { return &m_AssetManager; }
