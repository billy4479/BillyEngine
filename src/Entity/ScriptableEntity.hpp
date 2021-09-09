#pragma once

#include "../Core/Common.hpp"
#include "Entity.hpp"

namespace BillyEngine {
class ScriptableEntity {
   public:
    BE_NON_COPY_CONSTRUTIBLE(ScriptableEntity)

    ScriptableEntity(entt::entity handle, EntityManager* application);
    ScriptableEntity(Entity e);

    virtual ~ScriptableEntity() = default;

   protected:
    virtual void OnCreate() = 0;
    virtual void OnUpdate(f64) = 0;
    virtual void OnDestroy() = 0;

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

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine