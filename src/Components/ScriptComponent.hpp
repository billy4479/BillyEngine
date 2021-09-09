#pragma once

#include "../Core/Common.hpp"
#include "../Entity/ScriptableEntity.hpp"

namespace BillyEngine {

namespace Components {

struct Script {
    std::function<void()> Instantiate;
    std::function<void()> DestroyInstance;

    std::function<void(ScriptableEntity*)> OnCreate;
    std::function<void(ScriptableEntity*, f32)> OnUpdate;
    std::function<void(ScriptableEntity*)> OnDestroy;

    ~Script() {
        if (Instance != nullptr) DestroyInstance();
    }

    template <typename T, typename... Args>
    void Bind(Entity e, Args&&... args) {
        Instantiate = [&, e]() {
            BE_ASSERT(Instance == nullptr);
            Instance = new T(e, std::forward<Args>(args)...);
        };
        DestroyInstance = [&]() {
            BE_ASSERT(Instance != nullptr);

            OnDestroy(Instance);
            delete static_cast<T*>(Instance);
            Instance = nullptr;
        };

        OnCreate = [&](ScriptableEntity* instance) {
            BE_ASSERT(Instance != nullptr);

            dynamic_cast<T*>(instance)->OnCreate();
        };
        OnUpdate = [&](ScriptableEntity* instance, f32 delta) {
            BE_ASSERT(Instance != nullptr);

            dynamic_cast<T*>(instance)->OnUpdate(delta);
        };
        OnDestroy = [&](ScriptableEntity* instance) {
            BE_ASSERT(Instance != nullptr);

            dynamic_cast<T*>(instance)->OnDestroy();
        };
    }

    ScriptableEntity* Instance = nullptr;

    Script(const Script& other) = delete;
    Script(Script&& other) {
        this->Instance = other.Instance;
        this->Instantiate = other.Instantiate;
        this->DestroyInstance = other.DestroyInstance;
        this->OnCreate = other.OnCreate;
        this->OnUpdate = other.OnUpdate;
        this->OnDestroy = other.OnDestroy;

        other.Instance = nullptr;
    }
    Script& operator=(Script&& other) {
        if (this != &other) {
            this->Instance = other.Instance;
            this->Instantiate = other.Instantiate;
            this->DestroyInstance = other.DestroyInstance;
            this->OnCreate = other.OnCreate;
            this->OnUpdate = other.OnUpdate;
            this->OnDestroy = other.OnDestroy;

            other.Instance = nullptr;
        }
        return *this;
    }
    Script() = default;
};
}  // namespace Components
}  // namespace BillyEngine