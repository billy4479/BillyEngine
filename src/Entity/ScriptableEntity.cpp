#include "ScriptableEntity.hpp"

#include "../Application.hpp"
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

Components::Transform& ScriptableEntity::Transform() {
    return GetComponent<Components::Transform>();
}

Components::Tag& ScriptableEntity::Tag() {
    return GetComponent<Components::Tag>();
}

}  // namespace BillyEngine