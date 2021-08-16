#pragma once

#include "../Core/Common.hpp"
#include "Entity.hxx"

namespace BillyEngine {
class ScriptableEntity : public Entity {
   public:
    ScriptableEntity(entt::entity handle, Application *application)
        : Entity(handle, application) {}
    ScriptableEntity(Entity e) : Entity(e) {}

    virtual ~ScriptableEntity() = default;

   protected:
    virtual void OnCreate() = 0;
    virtual void OnUpdate(f32) = 0;
    virtual void OnDestroy() = 0;
};

}  // namespace BillyEngine