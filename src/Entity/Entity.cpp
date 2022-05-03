#include "Entity/Entity.hpp"

#include <entt/entt.hpp>

#include "Core/Logger.hpp"
#include "Entity/Components.hpp"
#include "Entity/EntityManager.hpp"

namespace BillyEngine {

Entity::Entity() : m_ID(entt::null), m_EntityManager(nullptr) {}
Entity::Entity(entt::entity id, EntityManager& em)
    : m_ID(id), m_EntityManager(&em) {}

Entity::operator bool() const {
    return m_ID != entt::null && m_EntityManager != nullptr;
}

template <typename T>
T& Entity::GetComponent() {
    auto& reg = m_EntityManager->GetInternalRegistry();
    return reg.get<T>(*this);
}

template <typename T>
T& Entity::AddComponent(T&& component) {
    auto& reg = m_EntityManager->GetInternalRegistry();
    return reg.emplace<T>(*this, std::move(component));
}

template <typename T>
void Entity::RemoveComponent() {
    auto& reg = m_EntityManager->GetInternalRegistry();
    reg.remove<T>(*this);
}

#define SPECIALIZE(T)                      \
    template T& Entity::GetComponent();    \
    template T& Entity::AddComponent(T&&); \
    template void Entity::RemoveComponent<T>();

SPECIALIZE(TransformComponent)
SPECIALIZE(IDComponent)
SPECIALIZE(TagComponent)
// SPECIALIZE(SpriteComponent);

#undef SPECIALIZE

}  // namespace BillyEngine