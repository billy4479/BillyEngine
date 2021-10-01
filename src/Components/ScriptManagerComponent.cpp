#include "ScriptManagerComponent.hpp"

#include "entt/entity/entity.hpp"

namespace BillyEngine {
namespace Components {

ScriptManager::ScriptManager(Entity e) : m_Entity(e) {}

#ifdef DEBUG
    #define REPLACER(...) [](__VA_ARGS__) { BE_ABORT(); }
#else
    #define REPLACER(...) nullptr
#endif

BillyEngine::Components::ScriptManager::ScriptManager(
    ScriptManager&& other) noexcept
    : m_Entity(other.m_Entity) {
    this->m_Components = other.m_Components;
    this->m_Entity = other.m_Entity;

    other.m_Components.clear();
    other.m_Entity.m_Handle = entt::null;
    other.m_Entity.m_EntityManager = nullptr;
    other.m_Entity.m_Registry = nullptr;
}

ScriptManager::~ScriptManager() = default;

BillyEngine::Components::ScriptManager&
BillyEngine::Components::ScriptManager::operator=(
    ScriptManager&& other) noexcept {
    if (this != &other) {
        this->m_Components = other.m_Components;
        this->m_Entity = other.m_Entity;

        other.m_Components.clear();
        other.m_Entity.m_Handle = entt::null;
        other.m_Entity.m_EntityManager = nullptr;
        other.m_Entity.m_Registry = nullptr;
    }
    return *this;
}

void ScriptManager::CreateAll() {
    for (auto& ac : m_Components) {
        if (ac.HasToBeCreated) {
            ac.OnCreate(m_Entity);
            ac.HasToBeCreated = false;
        }
    }
}

void ScriptManager::UpdateAll(f32 delta) {
    for (auto& ac : m_Components) {
        ac.OnUpdate(m_Entity, delta);
    }
}

void ScriptManager::UnregisterScript(void* currentPtr) {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        if (it->IsStillThere(m_Entity) &&
            it->GetCurrentVoidPtr(m_Entity) == currentPtr) {
            m_Components.erase(it);
            break;
        }
    }
}

void ScriptManager::RegisterAllComponents() {
    for (auto& ac : m_Components) {
        if (ac.HasToRegisterComponents) {
            ac.RegisterComponents(m_Entity);
            ac.HasToRegisterComponents = false;
        }
    }
}
}  // namespace Components
}  // namespace BillyEngine