#pragma once

#define SDL_MAIN_HANDLED

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Entity/EntityManager.hpp"
#include "Rendering/Renderer.hpp"

namespace BillyEngine {
class DrawableTexture;
class Application {
   public:
    Application(const std::string &name, i32 width, i32 height)
        : Application(name, {width, height}) {}
    Application(const std::string &name, glm::ivec2 size);
    ~Application();

    void Run();
    AssetManager *GetAssetManager();
    EntityManager *GetEntityManager();
    const glm::ivec2 GetSize() const { return m_Size; }
    DrawableTexture CreateDrawableTexture(glm::ivec2 size);

   private:
    bool isRunning = false;
    void AskToStop();
    void OnUpdate(f32);
    Renderer *GetRenderer();

    static constexpr i32 FPS = 60;
    static constexpr i32 frameDelay = 1000 / FPS;

    glm::ivec2 m_Size;
    std::string m_Title;

    SDL_Window *m_Window;
    AssetManager m_AssetManager;
    Renderer m_Renderer;
    EventHandler m_EventHandler;
    EntityManager m_EntityManager;

    friend class Entity;
    friend class EntityManager;
    friend class AssetManager;
};
}  // namespace BillyEngine