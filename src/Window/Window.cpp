#include "Window.hpp"

#include <SDL_video.h>

namespace BillyEngine {
Window::Window(std::string_view title, glm::ivec2 size) {
    BE_PROFILE_FUNCTION();

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error("SDL_image failed to initialize.");

    m_Window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, size.x, size.y, 0);

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
    m_Resizable = resizable;
}

bool Window::IsResizable() { return m_Resizable; }

void Window::SetFullScreen(bool fullscreen) {
    SDL_SetWindowFullscreen(m_Window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    m_Fullscreen = fullscreen;
}

bool Window::IsFullScreen() { return m_Fullscreen; }

const glm::ivec2 Window::GetSize() const {
    i32 w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    return {w, h};
}

}  // namespace BillyEngine