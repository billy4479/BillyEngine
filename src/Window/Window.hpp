#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Window {
   public:
    Window(std::string_view title, glm::ivec2 size);
    ~Window();

    BE_NON_COPY_CONSTRUTIBLE(Window)

    void SetTitle(std::string_view title);
    const glm::ivec2 GetSize() const;

   private:
    glm::ivec2 m_Size;
    SDL_Window* m_Window = nullptr;
    std::function<void()> m_DestructionCallback;

    friend class Application;
};
}  // namespace BillyEngine