#pragma once

#define SDL_MAIN_HANDLED

#include "Core/Common.hpp"
#include "Entity/Entity.hpp"
#include "Event/EventManager.hpp"
#include "Wrappers/Fwd.hpp"

namespace BillyEngine {
class DrawableTexture;
class AssetManager;
class FPSManager;
class EntityManager;
class Renderer;
class Window;

struct AppConfig {
    std::string_view Title = "BillyEngine";
    glm::ivec2 Size = {1280, 720};
    bool Resizable = true;
    bool Fullscreen = false;
    bool Maximized = false;
    bool Borderless = false;
    std::filesystem::path AssetsPath = "";
    f32 TargetFPS = 60;
};

class Application {
   public:
    Application(const AppConfig & = AppConfig());
    ~Application();

    BE_NON_COPY_CONSTRUCTIBLE(Application)

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
     * @brief Create a new Entity
     *
     * @param name The name of the new Entity (tag component)
     * @return The created entity
     */
    Entity CreateEntity(const std::string &name = "");

    /**
     * @brief Create a Entity and adds a EntityBehavior
     *
     * @tparam T the type of the EntityBehavior
     * @param name The name of the new Entity (tag component)
     * @return T& The created EntityBehavior instance
     */
    template <typename T>
    inline T &CreateEntityAndAddBehavior(const std::string &name = "") {
        auto e = CreateEntity(name);
        return e.AddComponent<T>(e);
    }

    /**
     * @brief Destroy an Entity
     *
     * @param entity The Entity to destroy
     */
    void DestroyEntity(Entity entity);

    /**
     * @brief Duplicates an Entity and all its components
     *
     * @note The entities will have different IDs
     *
     * @param entity The source entity
     * @param name The name of the new entity (optional)
     * @return Entity The resulting entity
     */
    Entity DuplicateEntity(Entity entity, std::string_view name = "");

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
    void SetAssetFolder(const std::filesystem::path &path);

    /**
     * @brief Get the asset folder path
     *
     * This returns the current base path used when calling functions which load
     * assets (e.g.: `LoadFont` or `LoadImage`).
     *
     * @return std::filesystem::path The current assets path
     */
    std::filesystem::path GetAssetFolder();

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
    Ref<Font> LoadFont(const std::filesystem::path &path,
                       const std::string &name, u32 size);

    /**
     * @brief Get a font loaded previously using `LoadFont`
     *
     * @param name The name used when the font was loaded
     * @return TTF_Font* The font
     */
    Ref<Font> GetFont(const std::string &name);

    // TODO: maybe return a DrawableTexture?

    /**
     * @brief Load an image file (png or jpg)
     *
     * @param path Relative path to the image file
     * @param name The name this image will have
     * @return SDL_Surface* A surface containing the loaded image data
     */
    Ref<Surface> LoadImage(const std::filesystem::path &path,
                           const std::string name);

    /**
     * @brief Get a previously loaded image using `LoadImage`
     *
     * @param name The name used when the image was loaded
     * @return SDL_Surface* The image surface
     */
    Ref<Surface> GetImage(const std::string &name);

   public:
    /*** Window proxy ***/

    /**
     * @brief Get the window size
     *
     * @return const glm::ivec2 The window size
     */
    const glm::ivec2 GetSize() const;

    /**
     * @brief Set the window title
     *
     * @param title The new title
     */
    void SetTitle(std::string_view title);

    /**
     * @brief Set whether the window is resizable or not
     *
     * @param resizable If the window is resizable
     */
    void SetResizable(bool resizable);

    /**
     * @brief Set whether the window is fullscreen or not
     *
     * @param fullscreen If the window is fullscreen
     */
    void SetFullscreen(bool fullscreen);

    /**
     * @brief Check if the window is resizable
     *
     * @return true The window is resizable
     * @return false The window is not resizable
     */
    bool IsResizable() const;

    /**
     * @brief Check if the window is fullscreen
     *
     * @return true The window is fullscreen
     * @return false The window is not fullscreen
     */
    bool IsFullscreen() const;

    /**
     * @brief Check if the window has keyboard focus
     *
     * @return true The window has focus
     * @return false The window does not have focus
     */
    bool HasFocus() const;

    /**
     * @brief Raise the window abothe the other and get input focus
     *
     */
    void GetFocus();

    /**
     * @brief Check if the window is borderless
     *
     * @return true If the window is borderless
     * @return false If the window is not borderless
     */
    bool IsBorderless() const;

    /**
     * @brief Set whether the window is borderless or not
     *
     */
    void SetBorderless(bool);

   public:
    /*** FPSManager proxy ***/

    /**
     * @brief Get FPS
     *
     * @return f32 FPS
     */
    f32 GetFPS() const;

    /**
     * @brief Get the target (max) FPS
     *
     * @return f32 Target FPS
     */
    f32 GetTargetFPS() const;

    /**
     * @brief Set the target (max) FPS
     *
     * @param fps Target FPS
     */
    void SetTargetFPS(f32 fps);

    /**
     * @brief Get the number of frames since the engine start
     *
     * @return u64 The number of frames
     */
    u64 GetFrameCount() const;

   public:
    /*** EventManager proxy ***/

    /**
     * @brief Fire a custom event
     *
     * @param event The event to be fired, derived from Event
     * @return true If the event was handled
     * @return false It the event was not handled
     */
    bool FireEvent(Event &&event);

    /**
     * @brief Register a event listener
     *
     * The provided function gets called every time an event occurs and it has
     * to return true if the event was handled by it or false if it wasn't
     *
     * @param listener On event callback
     * @return u32 Listener ID
     */
    u32 RegisterEventListener(std::function<bool(Event &)> listener);

    /**
     * @brief Unregister a event listener by ID
     *
     * @param id The listener ID (provided at listener's registration)
     */
    void UnregisterEventListener(u32 id);

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
        return m_EventManager->RegisterListenerForEventType<T>(listener);
    }

   private:
    bool isRunning = false;
    void Frame(f32);

   private:
    Scope<EventManager> m_EventManager;
    Scope<Window> m_Window;
    Scope<AssetManager> m_AssetManager;
    Scope<EntityManager> m_EntityManager;
    Scope<Renderer> m_Renderer;
    Scope<FPSManager> m_FPSManager;

    static Application *s_Instance;

    friend class Entity;
    friend class EntityManager;
    friend class AssetManager;
    friend class Input;
};
}  // namespace BillyEngine