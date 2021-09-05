#include "Window.hpp"

namespace BillyEngine {
Window::Window(std::string_view title, glm::ivec2 size) : m_Size(size) {
#ifdef DEBUG
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
#endif

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO))
        throw std::runtime_error("SDL failed to initialize.");
    if (TTF_Init()) throw std::runtime_error("SDL_ttf failed to initialize.");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        throw std::runtime_error("SDL_image failed to initialize.");

    m_Window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_Size.x, m_Size.y, 0);

#ifdef DEBUG
    if (m_Window == nullptr) dbg_print("%s\n", SDL_GetError());
#endif
    BE_ASSERT(m_Window != nullptr);
}

Window::~Window() {
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    m_DestructionCallback();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Window::SetTitle(std::string_view title) {
    SDL_SetWindowTitle(m_Window, title.data());
}

const glm::ivec2 Window::GetSize() const { return m_Size; }

}  // namespace BillyEngine