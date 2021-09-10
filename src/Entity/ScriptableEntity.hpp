#pragma once

#include "../Core/Common.hpp"
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

   private:
    Entity m_Entity;
};

}  // namespace BillyEngine