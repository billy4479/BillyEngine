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

        auto create = [](Entity e, std::function<void(Entity)> next) {
            if (e.HasComponent<T>()) e.GetComponent<T>().OnCreate();
            next(e);
        };

        auto update = [](Entity e, std::function<void(Entity, f32)> next,
                         f32 delta) {
            if (e.HasComponent<T>()) e.GetComponent<T>().OnUpdate(delta);
            next(e, delta);
        };

        auto oldOnCreate = AllOnCreate;
        AllOnCreate = [create, oldOnCreate](Entity e) {
            create(e, oldOnCreate);
        };

        auto oldOnUpdate = AllOnUpdate;
        AllOnUpdate = [update, oldOnUpdate](Entity e, f32 delta) {
            update(e, oldOnUpdate, delta);
        };
    }

    void CreateAll();
    void UpdateAll(f32 delta);

   private:
    std::function<void(Entity)> AllOnCreate = [](Entity) {};
    std::function<void(Entity, f32)> AllOnUpdate = [](Entity, f32) {};

    Entity m_Entity;
};

}  // namespace Components
}  // namespace BillyEngine