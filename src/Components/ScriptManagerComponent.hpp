#pragma once

#include "../Core/Common.hpp"
#include "../Entity/Entity.hpp"

namespace BillyEngine {
class EntityBehavior;
class Entity;

namespace Components {

class ScriptManager {
   public:
    ScriptManager(Entity);
    ~ScriptManager();

    BE_NON_COPY_CONSTRUCTIBLE(ScriptManager)

    ScriptManager(ScriptManager&& other) noexcept;
    ScriptManager& operator=(ScriptManager&& other) noexcept;

    template <typename T>
    void RegisterScript() {
        static_assert(std::is_base_of_v<EntityBehavior, T>,
                      "T must derive from EntityBehavior");
        // BE_ASSERT(m_Entity.HasComponent<T>());
        m_Components.emplace_back<AnonymousComponent>({
            [](Entity e) { e.GetComponentM<T>().OnCreate(); },
            [](Entity e, f32 delta) { e.GetComponentM<T>().OnUpdate(delta); },
            [](Entity dest) { dest.AddComponent<T>(dest); },
            [](Entity e, Entity dest) {
                // This should call the copy constructor
                dest.AddComponent<T>(e.GetComponent<T>());
            },
            [](Entity e) -> void* { return &e.GetComponentM<T>(); },
            [](Entity e) { return e.HasComponent<T>(); },
            true,
        });
    }

    void UnregisterScript(void* currentPtr);

    void CreateAll();
    void UpdateAll(f32 delta);

   private:
    struct AnonymousComponent {
        std::function<void(Entity)> OnCreate;
        std::function<void(Entity, f32)> OnUpdate;
        std::function<void(Entity)> AddToEntity;
        std::function<void(Entity, Entity)> CopyToEntity;
        std::function<void*(Entity)> GetCurrentVoidPtr;
        std::function<bool(Entity)> IsStillThere;
        bool HasToBeCreated;
    };

    std::vector<AnonymousComponent> m_Components;

    Entity m_Entity;
};

}  // namespace Components
}  // namespace BillyEngine