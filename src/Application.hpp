#pragma once

#define SDL_MAIN_HANDLED

#include "Components/ScriptComponent.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Event/EventHandler.hpp"
#include "Rendering/Renderer.hpp"
#include "Window/Window.hpp"
#include "Wrappers/Fwd.hpp"

namespace BillyEngine {
class DrawableTexture;
class Application {
   public:
    Application(std::string_view title, i32 width, i32 height,
                const std::filesystem::path &assetsPath = "")
        : Application(title, {width, height}, assetsPath) {}
    Application(std::string_view title, glm::ivec2 size,
                const std::filesystem::path &assetsPath = "");
    ~Application();

   public:
    void Run();
    inline f32 GetFPS() const { return m_ActualFps; };
    Ref<DrawableTexture> CreateDrawableTexture(glm::ivec2 size);
    void AskToStop();

    inline EventHandler &GetEventHandler() { return m_EventHandler; }

   public:
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
    T &CreateScriptableEntity(const std::string &name = "", Args &&...args) {
        static_assert(std::is_base_of<ScriptableEntity, T>(),
                      "T must be derived from ScriptableEntity");
        auto e = CreateEntity(name);
        auto &sc = e.AddComponent<Components::Script>();
        sc.Bind<T, Args...>(e, std::forward<Args>(args)...);
        return *sc.GetInstanceOrFail<T>();
    }

    /**
     * @brief Create a new Entity
     *
     * @param name The name of the new Entity (tag component)
     * @return The created entity
     */
    inline Entity CreateEntity(const std::string &name = "") {
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

   public:
    /*** AssetManager proxy ***/

    /**
     * @brief Set the assets folder
     *
     * When a call to functions which load assets is done (e.g.: `LoadFont` or
     * `LoadImage`) this will be used as base path.
     *
     * @note The path is relative to the executable location
     *
     * @param path The path to the folder (can be relative or absolute)
     */
    inline void SetAssetFolder(const std::filesystem::path &path) {
        m_AssetManager.SetAssetFolder(path);
    }

    /**
     * @brief Get the asset folder path
     *
     * This returns the current base path used when calling functions which load
     * assets (e.g.: `LoadFont` or `LoadImage`).
     *
     * @return std::filesystem::path The current assets path
     */
    inline std::filesystem::path GetAssetFolder() {
        return m_AssetManager.GetAssetFolder();
    }

    /**
     * @brief Load a TTF font
     *
     * @note path is relative to the assets folder
     *
     * @param path Relative path of the ttf file
     * @param name The name this font will have
     * @param size The size in pt
     * @return TTF_Font* The loaded font
     */
    inline Ref<Font> LoadFont(const std::filesystem::path &path,
                              const std::string &name, u32 size) {
        return m_AssetManager.LoadFont(path, name, size);
    }

    /**
     * @brief Get a font loaded previously using `LoadFont`
     *
     * @param name The name used when the font was loaded
     * @return TTF_Font* The font
     */
    inline Ref<Font> GetFont(const std::string &name) {
        return m_AssetManager.GetFont(name);
    }

    // TODO: maybe return a DrawableTexture?

    /**
     * @brief Load an image file (png or jpg)
     *
     * @param path Relative path to the image file
     * @param name The name this image will have
     * @return SDL_Surface* A surface containing the loaded image data
     */
    inline Ref<Surface> LoadImage(const std::filesystem::path &path,
                                  const std::string name) {
        return m_AssetManager.LoadImage(path, name);
    }

    /**
     * @brief Get a previously loaded image using `LoadImage`
     *
     * @param name The name used when the image was loaded
     * @return SDL_Surface* The image surface
     */
    inline Ref<Surface> GetImage(const std::string &name) {
        return m_AssetManager.GetImage(name);
    }

   public:
    /*** Window proxy ***/

    /**
     * @brief Get the window size
     *
     * @return const glm::ivec2 The window size
     */
    inline const glm::ivec2 GetSize() const { return m_Window.GetSize(); }

    /**
     * @brief Set the window title
     *
     * @param title The new title
     */
    inline void SetTitle(std::string_view title) { m_Window.SetTitle(title); }

   private:
    bool isRunning = false;
    void Frame(f32);
    Ref<Renderer> GetRenderer();

   private:
    static constexpr f32 FPS = 60;
    // Min frame time in milliseconds
    static constexpr u32 frameDelay = u32(1000.0f / FPS);

    f32 m_ActualFps = 0;

   private:
    Window m_Window;
    AssetManager m_AssetManager;
    EventHandler m_EventHandler;
    EntityManager m_EntityManager;
    Ref<Renderer> m_Renderer = nullptr;

    friend class Entity;
    friend class EntityManager;
    friend class AssetManager;
};
}  // namespace BillyEngine