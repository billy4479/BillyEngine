#include "ScriptableEntity.hpp"

#include "../Application.hpp"
#include "Entity.hpp"

namespace BillyEngine {

ScriptableEntity::ScriptableEntity(entt::entity handle, EntityManager *em)
    : m_Entity(handle, em) {}

ScriptableEntity::ScriptableEntity(Entity e) : m_Entity(e) {}

void ScriptableEntity::Destroy() {
    m_Entity.m_EntityManager->DestroyEntity(m_Entity);
}

}  // namespace BillyEngine