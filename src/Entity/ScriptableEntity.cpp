#include "ScriptableEntity.hpp"

#include "../Application.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "Entity.hpp"

namespace BillyEngine {

ScriptableEntity::ScriptableEntity(entt::entity handle, EntityManager* em)
    : m_Entity(handle, em) {
    BE_CORE_INFO("Create scriptable entity for {}", (u32)handle);
}

ScriptableEntity::ScriptableEntity(Entity e) : m_Entity(e) {
    BE_CORE_INFO("Create scriptable entity for {}", (u32)e);
}

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