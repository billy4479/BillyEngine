#include "Application.hpp"

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hxx"
#include "Entity/ScriptableEntity.hpp"

namespace BillyEngine {

Application::Application(const std::string &title, glm::ivec2 size)
    : m_Size(size),
      m_Title(title),
      m_AssetManager(this),
      m_EntityManager(this) {
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

    u32 frameStart = 0;
    i32 frameTime = 0;

    u32 lastDelta = 0;
    while (isRunning) {
        frameStart = SDL_GetTicks();
        m_Renderer.Clear();

        OnUpdate(lastDelta);

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

void Application::OnUpdate(f32 delta) {
    m_EventHandler.HandleEvents();

    m_EntityManager.Update(delta);

    m_Renderer.RenderToScreen();
}

Renderer *Application::GetRenderer() { return &m_Renderer; }

AssetManager *Application::GetAssetManager() { return &m_AssetManager; }

DrawableTexture Application::CreateDrawableTexture(glm::ivec2 size) {
    return m_Renderer.CreateDrawableTexture(size);
}

}  // namespace BillyEngine
