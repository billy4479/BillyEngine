#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Application;
class Window {
   public:
    Window(std::string_view title, glm::ivec2 size, Application*);
    ~Window();

    BE_NON_COPY_CONSTRUCTIBLE(Window)

    void SetTitle(std::string_view title);

    void SetResizable(bool);
    bool IsResizable() const;
    void SetFullScreen(bool);
    bool IsFullScreen() const;

    const glm::ivec2 GetSize() const;
    bool HasFocus() const;

   private:
    SDL_Window* m_Window = nullptr;
    bool m_Resizable = true;
    bool m_Fullscreen = false;
    bool m_Focus = true;

    friend class Application;
};
}  // namespace BillyEngine