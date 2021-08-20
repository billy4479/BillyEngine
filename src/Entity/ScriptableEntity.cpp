#include "ScriptableEntity.hpp"

#include "../Application.hpp"

namespace BillyEngine {

ScriptableEntity::ScriptableEntity(entt::entity handle,
                                   Application *application)
    : Entity(handle, application) {}

ScriptableEntity::ScriptableEntity(Entity e) : Entity(e) {}

void ScriptableEntity::Destroy() {
    m_Application->GetEntityManager()->DestroyEntity(*this);
}

}  // namespace BillyEngine