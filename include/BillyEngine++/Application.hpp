#pragma once

#include <glm/ext/vector_int2.hpp>

#include "Core/Types.hpp"

namespace BillyEngine {

class Window;
class Renderer;
class EventManager;
class Input;
class AssetManager;
class EntityManager;

class BE_API Application {
   public:
    ~Application();

    struct ApplicationProprieties {
        glm::ivec2 Size;
        std::string_view Title;
        bool VSync;
    };

    void Run();
    void Quit();

    static constexpr ApplicationProprieties DefaultProps = {
        .Size = {800, 600},
        .Title = "BillyEngine",
        .VSync = true,
    };

    static Application& The();
    static Application& CreateOrReset(
        const ApplicationProprieties& props = DefaultProps);

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
    Scope<EntityManager> m_EntityManager;

    Application(const ApplicationProprieties&);
    static Application* s_Instance;
};

}  // namespace BillyEngine