#pragma once

#include "Events/EventManager.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

class Application {
   public:
    Application();
    ~Application();

    void Run();
    void Quit();

   private:
    bool m_Running{false};

   private:
    Window m_Window;
    Renderer m_Renderer;
    EventManager m_EventManager;
};

}  // namespace BillyEngine