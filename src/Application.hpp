#pragma once

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Entity/Entity.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

class Application {
   public:
    Application(std::string, i32 width, i32 height);
    ~Application();

    void Run();
    Renderer *GetRenderer();
    AssetManager *GetAssetManager();
    Entity CreateEntity(const std::string &);
    void DestroyEntity(Entity);

   private:
    bool isRunning = false;
    void AskToStop();
    void OnCreate();
    void OnUpdate(f32);

    static constexpr i32 FPS = 60;
    static constexpr i32 frameDelay = 1000 / FPS;

    i32 m_Height, m_Width;
    std::string m_Title;

    SDL_Window *m_Window;
    AssetManager m_AssetManager;
    Renderer m_Renderer;
    EventHandler m_EventHandler;
    entt::registry m_EntityRegister;
};
}  // namespace BillyEngine