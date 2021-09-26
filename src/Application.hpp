#pragma once

#define SDL_MAIN_HANDLED

#include "Components/ScriptComponent.hpp"
#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/FPSManager.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/ScriptableEntity.hpp"
#include "Event/EventManager.hpp"
#include "Rendering/Renderer.hpp"
#include "Window/Window.hpp"
#include "Wrappers/Fwd.hpp"

namespace BillyEngine {
class DrawableTexture;
class Application {
   public:
    Application(std::string_view title = "BillyEngine",
                glm::ivec2 size = {1280, 720}, bool resizable = true,
                bool fullscreen = false,
                const std::filesystem::path &assetsPath = "");
    ~Application();

   public:
    /**
     * @brief Starts the application
     *
     */
    void Run();

    /**
     * @brief Stops the application
     *
     * @note The current frame will be completed
     */
    void Stop();

    /**
     * @brief Create a Drawable Texture
     *
     * @param size The DrawableTexture size in pixels
     * @return Ref<DrawableTexture> The created DrawableTexture
     */
    Ref<DrawableTexture> CreateDrawableTexture(glm::ivec2 size);

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

    /**
     * @brief Set whether the window is resizable or not
     *
     * @param resizable If the window is resizable
     */
    inline void SetResizable(bool resizable) {
        m_Window.SetResizable(resizable);
    }

    /**
     * @brief Set whether the window is fullscreen or not
     *
     * @param fullscreen If the window is fullscreen
     */
    inline void SetFullscreen(bool fullscreen) {
        m_Window.SetFullScreen(fullscreen);
    }

    /**
     * @brief Check if the window is resizable
     *
     * @return true The window is resizable
     * @return false The window is not resizable
     */
    inline bool IsResizable() const { return m_Window.IsResizable(); }

    /**
     * @brief Check if the window is fullscreen
     *
     * @return true The window is fullscreen
     * @return false The window is not fullscreen
     */
    inline bool IsFullscreen() const { return m_Window.IsFullScreen(); }

    /**
     * @brief Check if the window has keyboard focus
     *
     * @return true The window has focus
     * @return false The window does not have focus
     */
    inline bool HasFocus() const { return m_Window.HasFocus(); }

   public:
    /*** FPSManager proxy ***/

    /**
     * @brief Get FPS
     *
     * @return f32 FPS
     */
    inline f32 GetFPS() const { return m_FPSManager.GetActualFPS(); }

    /**
     * @brief Get the target (max) FPS
     *
     * @return f32 Target FPS
     */
    inline f32 GetTargetFPS() const { return m_FPSManager.GetTargetFPS(); }

    /**
     * @brief Set the target (max) FPS
     *
     * @param fps Target FPS
     */
    inline void SetTargetFPS(f32 fps) { m_FPSManager.SetTargetFPS(fps); }

   public:
    /*** EventManager proxy ***/

    /**
     * @brief Fire a custom event
     *
     * @param event The event to be fired, derived from Event
     * @return true If the event was handled
     * @return false It the event was not handled
     */
    inline bool FireEvent(Event &&event) {
        return m_EventManager.FireEvent(std::move(event));
    }

    /**
     * @brief Register a event listener
     *
     * The provided function gets called every time an event occurs and it has
     * to return true if the event was handled by it or false if it wasn't
     *
     * @param listener On event callback
     * @return u32 Listener ID
     */
    inline u32 RegisterEventListener(std::function<bool(Event &)> listener) {
        return m_EventManager.RegisterListener(listener);
    }

    /**
     * @brief Unregister a event listener by ID
     *
     * @param id The listener ID (provided at listener's registration)
     */
    inline void UnregisterEventListener(u32 id) {
        m_EventManager.UnregisterListener(id);
    }

    /**
     * @brief Register a event listener for a specific event type
     *
     * The provided function will be called on every event of the specified type
     * and it has to return true if the event was handled by it or false if it
     * wasn't
     *
     * @tparam T The event type
     * @param listener On event callback
     * @return u32 Listener ID
     */
    template <typename T>
    inline u32 RegisterEventListenerFor(std::function<bool(T &)> listener) {
        return m_EventManager.RegisterListenerForEventType<T>(listener);
    }

   private:
    bool isRunning = false;
    void Frame(f32);

   private:
    EventManager m_EventManager;
    Window m_Window;
    AssetManager m_AssetManager;
    EntityManager m_EntityManager;
    Renderer m_Renderer;
    FPSManager m_FPSManager;

    friend class Entity;
    friend class EntityManager;
    friend class AssetManager;
    friend class Input;
};
}  // namespace BillyEngine