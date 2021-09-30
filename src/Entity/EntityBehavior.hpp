#pragma once

#include "../Components/ScriptManagerComponent.hpp"
#include "../Core/Common.hpp"
#include "../Core/Logger.hpp"
#include "../Core/UUID.hpp"
#include "Entity.hpp"

namespace BillyEngine {

namespace Components {
class Transform;
class Tag;
}  // namespace Components
class Application;

class EntityBehavior {
   public:
    EntityBehavior(entt::entity handle, EntityManager*);
    EntityBehavior(Entity e);

    virtual ~EntityBehavior() {
        // If we are destroying the whole entity ScriptManager may be destroyed
        // before this
        if (HasComponent<Components::ScriptManager>())
            GetComponentM<Components::ScriptManager>().UnregisterScript(this);
    };

    /**
     * @brief Destroy this entity
     *
     */
    void Destroy();

    /**
     * @brief Destroy e
     *
     * @param e The entity to destroy
     */
    void Destroy(Entity e);

    inline operator Entity() const { return m_Entity; }

    /**
     * @brief Add a component
     *
     * @note Component are unique
     *
     * @tparam T Component type
     * @tparam Args Type of the arguments to pass T constructor (deduced)
     * @param args Arguments to pass T constructor
     * @return T& The new component
     */
    template <typename T, typename... Args>
    inline T& AddComponent(Args&&... args) {
        return m_Entity.AddComponent<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes a component
     *
     * @tparam T the type of the component to remove
     */
    template <typename T>
    inline void RemoveComponent() {
        m_Entity.RemoveComponent<T>();
    }

    /**
     * @brief Checks if has a component
     *
     * @tparam T The component type
     * @return true If it has T
     * @return false If it doesn't have T
     */
    template <typename T>
    inline bool HasComponent() {
        return m_Entity.HasComponent<T>();
    }

    /**
     * @brief Get a component
     *
     * @tparam T The type of the component
     * @return T& The corresponding component
     */
    template <typename T>
    inline T& GetComponentM() {
        return m_Entity.GetComponentM<T>();
    }
    /**
     * @copydoc GetComponent
     */
    template <typename T>
    const inline T& GetComponent() const {
        return m_Entity.GetComponent<T>();
    }

    /**
     * @brief Helper to get the Transform component
     *
     * @return Components::Transform& The Transform component
     */
    Components::Transform& TransformM();
    /**
     * @copydoc Transform
     */
    const Components::Transform& Transform() const;

    /**
     * @brief Helper to get the Tag component
     *
     * @return Components::Tag& The Tag component
     */
    Components::Tag& TagM();
    /**
     * @copydoc Tag
     */
    const Components::Tag& Tag() const;

    /**
     * @brief Helper to get the UUID of the entity
     *
     * @return const UUID The UUID of the entity
     */
    const UUID ID() const;

    /**
     * @brief Find a entity by UUID
     *
     * @param uuid The UUID to search for
     * @return Entity The entity, if found, or a null entity
     */
    Entity FindEntityByID(UUID uuid);

    /**
     * @brief Find a entity by tag
     *
     * @param tag The tag name to search for
     * @return Entity The entity, if found, or a null entity
     */
    Entity FindEntityByTag(std::string_view tag);

    virtual void OnCreate() = 0;
    virtual void OnUpdate(f32) = 0;

   protected:
    /**
     * @brief Internal function. DO NOT CALL!!!
     *
     * This function is automatically called in the constructor
     */
    template <typename T>
    void Bind() {
        if (!HasComponent<Components::ScriptManager>())
            AddComponent<Components::ScriptManager>(m_Entity)
                .RegisterScript<T>();
        else
            GetComponentM<Components::ScriptManager>().RegisterScript<T>();
    }

    struct EntityLog {
#define LOG_FN(name, scope)                      \
    template <typename... Args>                  \
    inline void name(Args&&... args) const {     \
        BE_##scope(std::forward<Args>(args)...); \
    }

        LOG_FN(Trace, TRACE)
        LOG_FN(Debug, INFO)
        LOG_FN(Warning, WARN)
        LOG_FN(Error, ERROR)
        LOG_FN(Critical, CRITICAL)

#undef LOG_FN
    };
    /**
     * @brief A interface with the logger
     *
     */
    EntityLog Log;

    /**
     * @brief Get the Application object
     *
     * @return Application& The Application object
     */
    Application& App() const noexcept;

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine

#define SCRIPTABLE_ENTITY(className)                                    \
    className(BillyEngine::Entity e) : BillyEngine::EntityBehavior(e) { \
        Bind<className>();                                              \
    }
