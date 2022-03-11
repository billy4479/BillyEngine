#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

class Window;
class Renderer;
class EventManager;

class Application {
   public:
    Application();
    ~Application();

    void Run();
    void Quit();

   private:
    bool m_Running{false};

   private:
    Scope<Window> m_Window;
    Scope<Renderer> m_Renderer;
    Scope<EventManager> m_EventManager;
};

}  // namespace BillyEngine