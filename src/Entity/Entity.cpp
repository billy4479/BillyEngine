#include "Entity.hpp"

#include "../Core/Common.hpp"
#include "EntityManager.hpp"

namespace BillyEngine {

Entity::Entity(entt::entity handle, EntityManager* em)
    : m_Handle(handle), m_Registry(&em->m_Registry), m_EntityManager(em) {}

}  // namespace BillyEngine