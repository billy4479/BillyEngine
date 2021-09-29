#include "EntityBehavior.hpp"

#include "../Application.hpp"
#include "../Components/IDComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "Entity.hpp"

namespace BillyEngine {

EntityBehavior::EntityBehavior(entt::entity handle, EntityManager* em)
    : App(*em->m_Application), m_Entity(handle, em) {}

EntityBehavior::EntityBehavior(Entity e)
    : App(*e.m_EntityManager->m_Application), m_Entity(e) {}

void EntityBehavior::Destroy() {
    m_Entity.m_EntityManager->DestroyEntity(m_Entity);
}

void EntityBehavior::Destroy(Entity e) {
    m_Entity.m_EntityManager->DestroyEntity(e);
}

Components::Transform& EntityBehavior::Transform() {
    return GetComponent<Components::Transform>();
}

Components::Tag& EntityBehavior::Tag() {
    return GetComponent<Components::Tag>();
}

const UUID EntityBehavior::ID() {
    return static_cast<UUID>(GetComponent<Components::ID>());
}

Entity EntityBehavior::FindEntityByID(UUID id) {
    return m_Entity.m_EntityManager->FindEntityByID(id);
}

Entity EntityBehavior::FindEntityByTag(std::string_view tag) {
    return m_Entity.m_EntityManager->FindEntityByTag(tag);
}

}  // namespace BillyEngine