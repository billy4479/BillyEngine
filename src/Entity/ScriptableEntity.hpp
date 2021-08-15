#pragma once

#include "../Components/ScriptComponent.hpp"
#include "../Core/Common.hpp"
#include "Entity.hpp"

namespace BillyEngine {
// TODO: Try to remove `dynamic_cast` calls. See
// https://stackoverflow.com/questions/5694265/how-expensive-are-dynamic-casts-in-c
class ScriptableEntity : public Entity {
   public:
    ScriptableEntity(entt::entity handle, entt::registry *registry)
        : Entity(handle, registry),
          m_ScriptComponent(AddComponent<Components::ScriptComponent>(
              OnCreateE, OnUpdateE, OnDestroyE)) {}

    virtual void OnCreate() {}
    virtual void OnUpdate(f32) {}
    virtual void OnDestroy() {}

    bool IsScriptable() const override { return true; }

   private:
    Components::ScriptComponent &m_ScriptComponent;
    static inline void OnCreateE(Entity e) {
        assert(e.IsScriptable());

        auto sePtr = dynamic_cast<ScriptableEntity *>(&e);
        assert(sePtr != nullptr);

        sePtr->OnCreate();
    }
    static inline void OnUpdateE(Entity e, f32 delta) {
        assert(e.IsScriptable());

        auto sePtr = dynamic_cast<ScriptableEntity *>(&e);
        assert(sePtr != nullptr);

        sePtr->OnUpdate(delta);
    }
    static inline void OnDestroyE(Entity e) {
        assert(e.IsScriptable());

        auto sePtr = dynamic_cast<ScriptableEntity *>(&e);
        assert(sePtr != nullptr);

        sePtr->OnDestroy();
    }
};

}  // namespace BillyEngine