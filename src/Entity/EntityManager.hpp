#pragma once

#include "../Core/Common.hpp"
#include "../Core/UUID.hpp"

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

    Entity FindEntityByID(UUID);
    Entity FindEntityByTag(std::string_view);

   private:
    entt::registry m_Registry;
    Application *m_Application = nullptr;
    std::vector<entt::entity> m_DestructionQueue;

    void HandleDestruction() noexcept;

    friend class Application;
    friend class Entity;
    friend class ScriptableEntity;
};
}  // namespace BillyEngine