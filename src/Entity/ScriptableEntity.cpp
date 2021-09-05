#include "ScriptableEntity.hpp"

#include "../Application.hpp"

namespace BillyEngine {

ScriptableEntity::ScriptableEntity(entt::entity handle,
                                   Application *application)
    : m_Entity(handle, application) {}

ScriptableEntity::ScriptableEntity(Entity e) : m_Entity(e) {}

void ScriptableEntity::Destroy() {
    m_Entity.m_Application->DestroyEntity(m_Entity);
}

}  // namespace BillyEngine