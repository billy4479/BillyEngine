#include "Entity/EntityManager.hpp"

#include <entt/entt.hpp>

#include "Entity/Components.hpp"

namespace BillyEngine {

EntityManager::EntityManager() { m_Registry = CreateScope<entt::registry>(); }

EntityManager::~EntityManager() {}

Entity EntityManager::NewEntity(std::string_view name) {
    Entity e = {m_Registry->create(), *this};

    m_Registry->emplace<IDComponent>(e);
    m_Registry->emplace<TagComponent>(e, name);
    m_Registry->emplace<TransformComponent>(e);

    return e;
}

void EntityManager::DestroyEntity(Entity& e) {
    m_Registry->destroy(e.m_ID);
    e.m_ID = entt::null;
}

entt::registry& EntityManager::GetInternalRegistry() { return *m_Registry; }

Entity EntityManager::GetEntityByID(UUID id) {
    for (auto e : m_Registry->view<IDComponent>())
        if (m_Registry->get<IDComponent>(e).ID() == id) return Entity(e, *this);

    return Entity();
}

Entity EntityManager::GetEntityByName(std::string_view name) {
    for (auto e : m_Registry->view<TagComponent>())
        if (m_Registry->get<TagComponent>(e).Tag == name)
            return Entity(e, *this);

    return Entity();
}

}  // namespace BillyEngine