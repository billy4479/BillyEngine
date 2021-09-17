#pragma once

#include "../Core/Common.hpp"
#include "../Core/Logger.hpp"
#include "Entity.hpp"

namespace BillyEngine {
class ScriptableEntity {
   public:
    ScriptableEntity(entt::entity handle, EntityManager* application);
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

    inline Application* GetApplication() {
        return m_Entity.m_EntityManager->m_Application;
    }

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

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine