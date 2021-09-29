#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class EntityManager;
namespace Components {
class ScriptManager;
}
class Entity {
   public:
    Entity(entt::entity handle, EntityManager* em);
    Entity(const Entity& other) = default;

    ~Entity() = default;

    inline bool operator==(const Entity& other) {
        return this->m_Handle == other.m_Handle &&
               &this->m_Registry == &other.m_Registry;
    }
    inline bool operator!=(const Entity& other) { return !(*this == other); }
    inline operator bool() const { return m_Handle != entt::null; }
    inline operator entt::entity() const { return m_Handle; }
    inline operator u32() const { return (u32)m_Handle; }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        BE_ASSERT(!HasComponent<T>());
        T& component =
            m_Registry->emplace<T>(m_Handle, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    void RemoveComponent() {
        BE_ASSERT(HasComponent<T>());
        m_Registry->remove<T>(m_Handle);
    }

    template <typename T>
    bool HasComponent() const {
        BE_ASSERT(m_Registry->valid(m_Handle));
        return m_Registry->all_of<T>(m_Handle);
    }

    template <typename T>
    T& GetComponent() {
        BE_ASSERT(HasComponent<T>());
        return m_Registry->get<T>(m_Handle);
    }

    template <typename T>
    const T& GetComponent() const {
        BE_ASSERT(HasComponent<T>());
        return m_Registry->get<T>(m_Handle);
    }

   private:
    entt::entity m_Handle{entt::null};
    entt::registry* m_Registry;
    EntityManager* m_EntityManager = nullptr;

    friend class EntityBehavior;
    friend class Components::ScriptManager;
};
}  // namespace BillyEngine