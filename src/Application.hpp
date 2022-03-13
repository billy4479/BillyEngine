#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

class Window;
class Renderer;
class EventManager;
class Input;
class AssetManager;

class Application {
   public:
    ~Application();

    void Run();
    void Quit();

    static Application& The();
    static void Reset();

   private:
    Scope<AssetManager> m_AssetManager;
    Scope<Window> m_Window;
    Scope<Renderer> m_Renderer;
    Scope<EventManager> m_EventManager;
    Scope<Input> m_Input;

    Application();
    static Scope<Application> s_Instance;
};

}  // namespace BillyEngine