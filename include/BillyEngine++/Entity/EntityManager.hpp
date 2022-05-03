#pragma once

#include "Core/UUID.hpp"
#include "Entity/Entity.hpp"

// I'd like to avoid including entt here
// so I just forward declare some stuff
namespace entt {
enum class entity : BillyEngine::u32;
template <typename>
class basic_registry;
using registry = basic_registry<entity>;
}  // namespace entt

namespace BillyEngine {

class EntityManager {
   public:
    EntityManager();
    ~EntityManager();

    Entity NewEntity(std::string_view name = "");
    void DestroyEntity(Entity&);

    Entity GetEntityByID(UUID);
    Entity GetEntityByName(std::string_view);

    entt::registry& GetInternalRegistry();

   private:
    Scope<entt::registry> m_Registry{};
};

}  // namespace BillyEngine