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

    inline AssetManager& GetAssetManager() { return *m_AssetManager; }
    inline Window& GetWindow() { return *m_Window; }
    inline Renderer& GetRenderer() { return *m_Renderer; }
    inline EventManager& GetEventManager() { return *m_EventManager; }
    inline Input& GetInput() { return *m_Input; }

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