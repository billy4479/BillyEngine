#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Application;
struct AppConfig;
class Window {
   public:
    Window(const AppConfig&, Application*);
    ~Window();

    BE_NON_COPY_CONSTRUCTIBLE(Window)

    void SetTitle(std::string_view title);

    void SetResizable(bool);
    bool IsResizable() const;
    void SetFullScreen(bool);
    bool IsFullScreen() const;
    void SetBorderless(bool);
    bool IsBorderless() const;
    void GetFocus() const;
    bool HasFocus() const;

    const glm::ivec2 GetSize() const;

   private:
    SDL_Window* m_Window = nullptr;
    Application* m_App = nullptr;

    friend class Application;
};
}  // namespace BillyEngine