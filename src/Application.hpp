#pragma once

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Entity/Entity.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {

class Application {
   public:
    Application(std::string, i32 width, i32 height);
    ~Application();

    void Run();
    Renderer *GetRenderer();
    AssetManager *GetAssetManager();
    template <class T>
    T CreateEntity(const std::string &name) {
        T e = {m_EntityRegister.create(), &m_EntityRegister};

        std::string n;
        if (name.empty()) {
            std::stringstream ss;
            ss << "Entity [" << (u32)e << "]";
            ss >> n;
        } else {
            n = name;
        }

        AddBasicComponets(e, name);
        return e;
    }
    void DestroyEntity(Entity);

   private:
    bool isRunning = false;
    void AskToStop();
    void OnCreate();
    void OnUpdate(f32);

    void AddBasicComponets(Entity &, const std::string &);

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