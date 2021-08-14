#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Entity {
   public:
    Entity() = default;
    Entity(entt::entity handle, entt::registry* registry)
        : m_Handle(handle), m_Registry(registry) {}
    Entity(const Entity& other) = default;

    ~Entity() = default;

    inline bool operator==(const Entity& other) {
        return this->m_Handle == other.m_Handle &&
               this->m_Registry == other.m_Registry;
    }
    inline bool operator!=(const Entity& other) { return !(*this == other); }
    inline operator bool() const { return m_Handle != entt::null; }
    inline operator entt::entity() const { return m_Handle; }
    inline operator u32() const { return (u32)m_Handle; }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        assert(!HasComponent<T>());
        T& component =
            m_Registry->emplace<T>(m_Handle, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    void RemoveComponent() {
        assert(HasComponent<T>());
        m_Registry->remove<T>(m_Handle);
    }

    template <typename T>
    bool HasComponent() {
        return m_Registry->try_get<T>(m_Handle) != nullptr;
    }

    template <typename T>
    T& GetComponent() {
        return m_Registry->get<T>(m_Handle);
    }

   private:
    entt::entity m_Handle{entt::null};
    entt::registry* m_Registry = nullptr;
};
}  // namespace BillyEngine