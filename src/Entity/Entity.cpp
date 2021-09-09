#include "Entity.hpp"

#include "../Core/Common.hpp"
#include "EntityManager.hpp"

namespace BillyEngine {

Entity::Entity(entt::entity handle, EntityManager* em)
    : m_Handle(handle), m_EntityManager(em) {}

}  // namespace BillyEngine