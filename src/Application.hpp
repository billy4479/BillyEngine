#pragma once

#define SDL_MAIN_HANDLED

#include "Components/Components.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Entity/Entity.hxx"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

class Application {
   public:
    Application(const std::string &name, i32 width, i32 height)
        : Application(name, {width, height}) {}
    Application(const std::string &name, glm::ivec2 size);
    ~Application();

    void Run();
    Renderer *GetRenderer();
    AssetManager *GetAssetManager();
    const glm::ivec2 GetSize() const { return m_Size; }

    Entity CreateEntity(const std::string &name);
    void DestroyEntity(Entity);

    template <typename T, typename... Args>
    Entity CreateScriptableEntity(const std::string &name, Args &&...args) {
        auto e = CreateEntity(name);
        e.AddComponent<Components::Script>().Bind<T, Args...>(
            e, std::forward<Args>(args)...);
        return e;
    }

   private:
    bool isRunning = false;
    void AskToStop();
    void OnCreate();
    void OnUpdate(f32);

    static constexpr i32 FPS = 60;
    static constexpr i32 frameDelay = 1000 / FPS;

    glm::ivec2 m_Size;
    std::string m_Title;

    SDL_Window *m_Window;
    AssetManager m_AssetManager;
    Renderer m_Renderer;
    EventHandler m_EventHandler;
    entt::registry m_EntityRegister;

    friend class Entity;
};
}  // namespace BillyEngine