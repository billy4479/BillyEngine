#pragma once

#include "../Core/Common.hpp"
#include "../Entity/Entity.hpp"

namespace BillyEngine {
namespace Components {

struct ScriptComponent {
   public:
    std::function<void(Entity)> OnCreate = [](Entity) {};
    std::function<void(f32, Entity)> OnUpdate = [](f32, Entity) {};
    std::function<void(Entity)> OnDestroy = [](Entity) {};

    ScriptComponent(std::function<void(Entity)> onCreate,
                    std::function<void(f32, Entity)> onUpdate,
                    std::function<void(Entity)> onDestroy)
        : OnCreate(onCreate), OnUpdate(onUpdate), OnDestroy(onDestroy) {}
    ScriptComponent(const ScriptComponent&) = delete;
    ScriptComponent(ScriptComponent&& other) noexcept {
        this->OnCreate = other.OnCreate;
        this->OnDestroy = other.OnDestroy;
        this->OnUpdate = other.OnUpdate;
        this->m_Entity = other.m_Entity;
    }
    ScriptComponent& operator=(ScriptComponent&& other) noexcept {
        if (this != &other) {
            this->OnCreate = other.OnCreate;
            this->OnDestroy = other.OnDestroy;
            this->OnUpdate = other.OnUpdate;
            this->m_Entity = other.m_Entity;
        }
        return *this;
    }

    void Instantiate(Entity e) {
        assert(!IsInstantiated());
        m_Entity = e;
    }

    bool IsInstantiated() { return (entt::entity)m_Entity == entt::null; }

   private:
    Entity m_Entity{entt::null, nullptr};
};
}  // namespace Components
}  // namespace BillyEngine