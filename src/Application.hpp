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
    const glm::ivec2 GetSize() const { return m_Size; }
    DrawableTexture CreateDrawableTexture(glm::ivec2 size);

    /*** EntityManager proxy ***/

    /**
     * @brief Create a Scriptable Entity
     *
     * @note
     * T must implement `void OnCreate()`, `void OnUpdate(f32)` and
     * `void OnDestroy()`
     *
     * @tparam T The type of the Scriptable Entity
     * @tparam Args The types of parameters for the constructor of T, deduced
     * @param name The name of the new entity (tag component)
     * @param args Other parameters for the constructor of T
     * @return The created Entity
     */
    template <typename T, typename... Args>
    inline Entity CreateScriptableEntity(const std::string &name,
                                         Args &&...args) {
        return m_EntityManager.CreateScriptableEntity<T>(
            name, std::forward<Args>(args)...);
    }

    /**
     * @brief Create a new Entity
     *
     * @param name The name of the new Entity (tag component)
     * @return The created entity
     */
    inline Entity CreateEntity(const std::string &name) {
        return m_EntityManager.CreateEntity(name);
    }

    /**
     * @brief Destroy an Entity
     *
     * @param entity The Entity to destroy
     */
    inline void DestroyEntity(Entity entity) {
        m_EntityManager.DestroyEntity(entity);
    }

    // TODO: remove those / make them private
    AssetManager *GetAssetManager();

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