#pragma once

#include "../Application.hpp"
#include "../Core/Common.hpp"
#include "Entity.hxx"

namespace BillyEngine {

Entity::Entity(entt::entity handle, Application* application)
    : m_Handle(handle), m_Application(application) {}

template <typename T, typename... Args>
T& Entity::AddComponent(Args&&... args) {
    assert(!HasComponent<T>());
    T& component = m_Application->m_EntityManager.m_Registry.emplace<T>(
        m_Handle, std::forward<Args>(args)...);
    return component;
}

template <typename T>
void Entity::RemoveComponent() {
    assert(HasComponent<T>());
    m_Application->m_EntityManager.m_Registry.remove<T>(m_Handle);
}

template <typename T>
bool Entity::HasComponent() {
    return m_Application->m_EntityManager.m_Registry.try_get<T>(m_Handle) !=
           nullptr;
}

template <typename T>
T& Entity::GetComponent() {
    return m_Application->m_EntityManager.m_Registry.get<T>(m_Handle);
}

}  // namespace BillyEngine