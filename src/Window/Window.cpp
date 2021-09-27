#include "Window.hpp"

#include "../Application.hpp"
#include "../Event/EventManager.hpp"
#include "../Event/WindowEvents.hpp"

namespace BillyEngine {
Window::Window(const AppConfig &appConfig, Application *application)
    : m_App(application) {
    BE_PROFILE_FUNCTION();

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error("SDL_image failed to initialize.");

    u32 flags = 0;

    if (appConfig.Fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (appConfig.Resizable) flags |= SDL_WINDOW_RESIZABLE;
    if (appConfig.Borderless) flags |= SDL_WINDOW_BORDERLESS;
    if (appConfig.Maximized) flags |= SDL_WINDOW_MAXIMIZED;

    m_Window = SDL_CreateWindow(appConfig.Title.data(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, appConfig.Size.x,
                                appConfig.Size.y, flags);

    BE_CHECK_SDL_ERROR_AND_DIE();
}

Window::~Window() {
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Window::SetTitle(std::string_view title) {
    SDL_SetWindowTitle(m_Window, title.data());
}

void Window::SetResizable(bool resizable) {
    SDL_SetWindowResizable(m_Window, SDL_bool(resizable));
}

bool Window::IsResizable() const {
    return SDL_GetWindowFlags(m_Window) & SDL_WINDOW_RESIZABLE;
}

void Window::SetFullScreen(bool fullscreen) {
    SDL_SetWindowFullscreen(m_Window,
                            fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    if (fullscreen != IsFullScreen()) {
        auto size = GetSize();
        m_App->FireEvent(WindowResizeEvent(size.x, size.y));
    }
}

bool Window::IsFullScreen() const {
    return SDL_GetWindowFlags(m_Window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

void Window::SetBorderless(bool borderless) {
    SDL_SetWindowBordered(m_Window, SDL_bool(!borderless));
}

bool Window::IsBorderless() const {
    return SDL_GetWindowFlags(m_Window) & SDL_WINDOW_BORDERLESS;
}

void Window::GetFocus() const { SDL_RaiseWindow(m_Window); }

const glm::ivec2 Window::GetSize() const {
    i32 w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    return {w, h};
}

bool Window::HasFocus() const {
    return SDL_GetWindowFlags(m_Window) & SDL_WINDOW_INPUT_FOCUS;
}

}  // namespace BillyEngine