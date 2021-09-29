#include "EntityBehavior.hpp"

#include "../Application.hpp"
#include "../Components/IDComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

namespace BillyEngine {

EntityBehavior::EntityBehavior(entt::entity handle, EntityManager* em)
    : EntityBehavior(Entity(handle, em)) {}

EntityBehavior::EntityBehavior(Entity e) : m_Entity(e) {}

void EntityBehavior::Destroy() {
    m_Entity.m_EntityManager->DestroyEntity(m_Entity);
}

void EntityBehavior::Destroy(Entity e) {
    m_Entity.m_EntityManager->DestroyEntity(e);
}

const Components::Transform& EntityBehavior::Transform() const {
    return std::as_const(*this).GetComponent<Components::Transform>();
}

Components::Transform& EntityBehavior::TransformM() {
    return GetComponentM<Components::Transform>();
}

Components::Tag& EntityBehavior::TagM() {
    return GetComponentM<Components::Tag>();
}

const Components::Tag& EntityBehavior::Tag() const {
    return std::as_const(*this).GetComponent<Components::Tag>();
}

const UUID EntityBehavior::ID() const {
    return static_cast<UUID>(GetComponent<Components::ID>());
}

Entity EntityBehavior::FindEntityByID(UUID id) {
    return m_Entity.m_EntityManager->FindEntityByID(id);
}

Entity EntityBehavior::FindEntityByTag(std::string_view tag) {
    return m_Entity.m_EntityManager->FindEntityByTag(tag);
}

Application& EntityBehavior::App() const noexcept {
    return *m_Entity.m_EntityManager->m_Application;
}

}  // namespace BillyEngine