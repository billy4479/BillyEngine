#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Application;
class Entity;
class EntityManager {
   public:
    explicit EntityManager(Application *application);
    ~EntityManager();

    BE_NON_COPY_CONSTRUCTIBLE(EntityManager)

    void Update(f32 delta);
    Entity CreateEntity(const std::string &name);
    void DestroyEntity(Entity entity);

   private:
    entt::registry m_Registry;
    Application *m_Application = nullptr;

    friend class Application;
    friend class Entity;
    friend class ScriptableEntity;
};
}  // namespace BillyEngine