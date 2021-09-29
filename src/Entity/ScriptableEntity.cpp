#include "ScriptableEntity.hpp"

#include "../Application.hpp"
#include "../Components/IDComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "Entity.hpp"

namespace BillyEngine {

ScriptableEntity::ScriptableEntity(entt::entity handle, EntityManager* em)
    : App(*em->m_Application), m_Entity(handle, em) {}

ScriptableEntity::ScriptableEntity(Entity e)
    : App(*e.m_EntityManager->m_Application), m_Entity(e) {}

void ScriptableEntity::Destroy() {
    m_Entity.m_EntityManager->DestroyEntity(m_Entity);
}

void ScriptableEntity::Destroy(Entity e) {
    m_Entity.m_EntityManager->DestroyEntity(e);
}

Components::Transform& ScriptableEntity::Transform() {
    return GetComponent<Components::Transform>();
}

Components::Tag& ScriptableEntity::Tag() {
    return GetComponent<Components::Tag>();
}

const UUID ScriptableEntity::ID() {
    return static_cast<UUID>(GetComponent<Components::ID>());
}

Entity ScriptableEntity::FindEntityByID(UUID id) {
    return m_Entity.m_EntityManager->FindEntityByID(id);
}

Entity ScriptableEntity::FindEntityByTag(std::string_view tag) {
    return m_Entity.m_EntityManager->FindEntityByTag(tag);
}

}  // namespace BillyEngine