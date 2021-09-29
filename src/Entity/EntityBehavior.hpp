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

    virtual ~EntityBehavior() = default;

    void Destroy();
    void Destroy(Entity);

    inline operator u32() const { return (u32)m_Entity; }
    inline operator Entity() const { return m_Entity; }

    template <typename T, typename... Args>
    inline T& AddComponent(Args&&... args) {
        return m_Entity.AddComponent<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    inline void RemoveComponent() {
        m_Entity.RemoveComponent<T>();
    }

    template <typename T>
    inline bool HasComponent() {
        return m_Entity.HasComponent<T>();
    }

    template <typename T>
    inline T& GetComponent() {
        return m_Entity.GetComponent<T>();
    }

    template <typename T>
    const inline T& GetComponent() const {
        return m_Entity.GetComponent<T>();
    }

    Components::Transform& Transform();
    Components::Tag& Tag();
    const UUID ID() const;

    Entity FindEntityByID(UUID);
    Entity FindEntityByTag(std::string_view);

    virtual void OnCreate() {}
    virtual void OnUpdate(f32) {}

   protected:
    template <typename T>
    void Bind() {
        if (!HasComponent<Components::ScriptManager>())
            AddComponent<Components::ScriptManager>(m_Entity)
                .RegisterScript<T>();
        else
            GetComponent<Components::ScriptManager>().RegisterScript<T>();
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
    EntityLog Log;
    Application& App() const noexcept;

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine

#define SCRIPTABLE_ENTITY(className)                                    \
    className(BillyEngine::Entity e) : BillyEngine::EntityBehavior(e) { \
        Bind<className>();                                              \
    }
