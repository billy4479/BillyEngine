#pragma once

#include "Core/Types.hpp"

namespace entt {

enum class entity : BillyEngine::u32;

}

namespace BillyEngine {

class EntityManager;

class Entity {
   public:
    Entity();
    Entity(entt::entity, EntityManager& em);

    inline operator entt::entity() const { return m_ID; }
    operator bool() const;

    inline bool operator==(const Entity& other) const {
        return m_ID == other.m_ID && m_EntityManager == other.m_EntityManager;
    }
    inline bool operator!=(const Entity& other) const {
        return !(*this == other);
    }

    template <typename T>
    T& GetComponent();

    template <typename T>
    T& AddComponent(T&&);

    template <typename T>
    void RemoveComponent();

   private:
    entt::entity m_ID;
    EntityManager* m_EntityManager;

    friend class EntityManager;
};

}  // namespace BillyEngine