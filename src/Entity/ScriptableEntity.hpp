#pragma once

#include "../Core/Common.hpp"
#include "../Core/Logger.hpp"
#include "Entity.hpp"

namespace BillyEngine {

namespace Components {
class Transform;
class Tag;
}  // namespace Components

class ScriptableEntity {
   public:
    ScriptableEntity(entt::entity handle, EntityManager*);
    ScriptableEntity(Entity e);

    virtual ~ScriptableEntity() = default;

    void Destroy();

    inline operator u32() const { return (u32)m_Entity; }

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

    Components::Transform& Transform();
    Components::Tag& Tag();

    //    protected:

    void OnCreate() {}
    void OnUpdate(f32) {}
    void OnDestroy() {}

   protected:
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
    Application& App;

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine

#define SCRIPTABLE_ENTITY(className)                                       \
    className(BillyEngine::Entity e) : BillyEngine::ScriptableEntity(e) {} \
    BE_NON_COPY_CONSTRUCTIBLE(className)
