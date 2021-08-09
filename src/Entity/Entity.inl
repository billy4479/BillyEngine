#pragma once

#include "Entity.hpp"
#include "Register.hpp"

namespace Entity {

Entity::~Entity() { m_Reg.UnregisterEntity(*this); }

template <typename T>
inline void Entity::AddComponent(T&& component) {
    m_Reg.AddComponent(component);
}

template <typename T, typename... Args>
inline void Entity::AddComponent(Args&&... args) {
    m_Reg.AddComponent<T, Args...>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline void Entity::RemoveComponent() {
    m_Reg.RemoveComponent<T>(*this);
}

template <typename T>
inline bool Entity::HasComponent() {
    return m_Reg.HasComponent<T>(*this);
}

template <typename T>
inline T& Entity::GetComponent() {
    return m_Reg.GetComponent<T>(*this);
}

}  // namespace Entity