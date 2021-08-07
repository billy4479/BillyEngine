#include "Entity.hpp"

namespace Entity {

// void Entity::UpdateEntities(f32 deltaTime) {
//     for (auto e : Register) {
//         if (e->HasComponent<ScriptComponent>())
//             e->GetComponent<ScriptComponent>().OnUpdate(deltaTime);
//     }
// }

u32 Entity::NextID = 0;
}  // namespace Entity
