#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Window {
   public:
    Window(std::string_view title, glm::ivec2 size);
    ~Window();

    BE_NON_COPY_CONSTRUCTIBLE(Window)

    void SetTitle(std::string_view title);

    void SetResizable(bool);
    bool IsResizable();
    void SetFullScreen(bool);
    bool IsFullScreen();

    const glm::ivec2 GetSize() const;

   private:
    SDL_Window* m_Window = nullptr;
    bool m_Resizable = true;
    bool m_Fullscreen = false;

    friend class Application;
};
}  // namespace BillyEngine