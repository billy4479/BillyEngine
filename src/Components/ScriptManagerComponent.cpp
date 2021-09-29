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
    this->AllOnCreate = other.AllOnCreate;
    this->AllOnUpdate = other.AllOnUpdate;

    other.AllOnCreate = REPLACER(Entity);
    other.AllOnUpdate = REPLACER(Entity, f32);
}

ScriptManager::~ScriptManager() = default;

BillyEngine::Components::ScriptManager&
BillyEngine::Components::ScriptManager::operator=(
    ScriptManager&& other) noexcept {
    if (this != &other) {
        this->AllOnCreate = other.AllOnCreate;
        this->AllOnUpdate = other.AllOnUpdate;
        this->m_Entity = other.m_Entity;

        other.AllOnCreate = REPLACER(Entity);
        other.AllOnUpdate = REPLACER(Entity, f32);
        other.m_Entity.m_Handle = entt::null;
        other.m_Entity.m_EntityManager = nullptr;
        other.m_Entity.m_Registry = nullptr;
    }
    return *this;
}

void ScriptManager::CreateAll() {
    AllOnCreate(m_Entity);
    AllOnCreate = [](Entity) {};
}

void ScriptManager::UpdateAll(f32 delta) { AllOnUpdate(m_Entity, delta); }

}  // namespace Components
}  // namespace BillyEngine