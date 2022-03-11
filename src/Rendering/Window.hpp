#pragma once

#include <glm/ext/vector_int2.hpp>
#include <string_view>

struct GLFWwindow;

namespace BillyEngine {

class Window {
   public:
    Window(std::string_view title, glm::ivec2 size);
    ~Window();

    void SwapBuffers();

    bool ShouldClose();
    void SetShouldClose(bool);

   private:
    GLFWwindow* m_Window;

    friend class EventManager;
    friend class Input;
};

}  // namespace BillyEngine