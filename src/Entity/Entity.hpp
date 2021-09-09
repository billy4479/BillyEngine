#pragma once

#include "../Core/Common.hpp"
#include "EntityManager.hpp"

namespace BillyEngine {
class Entity {
   public:
    Entity(entt::entity handle, EntityManager* em);
    Entity(const Entity& other) = default;

    ~Entity() = default;

    inline bool operator==(const Entity& other) {
        // TODO: check for the same register
        return this->m_Handle == other.m_Handle;
    }
    inline bool operator!=(const Entity& other) { return !(*this == other); }
    inline operator bool() const { return m_Handle != entt::null; }
    inline operator entt::entity() const { return m_Handle; }
    inline operator u32() const { return (u32)m_Handle; }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        BE_ASSERT(!HasComponent<T>());
        T& component = m_EntityManager->m_Registry.emplace<T>(
            m_Handle, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    void RemoveComponent() {
        BE_ASSERT(HasComponent<T>());
        m_EntityManager->m_Registry.remove<T>(m_Handle);
    }

    template <typename T>
    bool HasComponent() {
        return m_EntityManager->m_Registry.try_get<T>(m_Handle) != nullptr;
    }

    template <typename T>
    T& GetComponent() {
        return m_EntityManager->m_Registry.get<T>(m_Handle);
    }

   private:
    entt::entity m_Handle{entt::null};
    EntityManager* m_EntityManager = nullptr;

    friend class ScriptableEntity;
};
}  // namespace BillyEngine