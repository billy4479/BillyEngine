#pragma once

#include "../Core/Common.hpp"
#include "../Entity/ScriptableEntity.hpp"

namespace BillyEngine {

namespace Components {

#ifdef BE_HAS_CPP20
template <typename T>
concept EntityScriptClass = requires {
    { std::declval<T>().OnCreate() } -> std::same_as<void>;
    { std::declval<T>().OnUpdate(std::declval<f32>()) } -> std::same_as<void>;
    { std::declval<T>().OnDestroy() } -> std::same_as<void>;
};
#else
    #define EntityScriptClass typename
#endif

struct Script {
    // std::function<void()> Instantiate;
    std::function<void()> DestroyInstance;

    std::function<void()> OnCreate;
    std::function<void(f32)> OnUpdate;
    std::function<void()> OnDestroy;

    std::function<void*()> GetInstanceAsVoidPtr = []() { return nullptr; };

    bool WasOnCreateCalled = false;
    ~Script() { DestroyInstance(); }

    template <EntityScriptClass T>
    inline T* GetInstanceOrFail() {
        if (GetInstanceAsVoidPtr() == nullptr) {
            BE_ABORT
        }
        auto r = static_cast<T*>(GetInstanceAsVoidPtr());
        BE_ASSERT(r != nullptr);
        return r;
    }

    template <EntityScriptClass T>
    inline T* GetInstanceOrNull() {
        auto r = static_cast<T*>(GetInstanceAsVoidPtr());
        BE_ASSERT(r != nullptr);
        return r;
    }

    template <EntityScriptClass T, typename... Args>
    void Bind(Entity e, Args&&... args) {
        T* instance = nullptr;

        // Instantiate = [&, e]() {
        // BE_ASSERT(instance == nullptr);
        instance = new T(e, std::forward<Args>(args)...);
        BE_ASSERT(instance != nullptr);

        DestroyInstance = [&, instance]() {
            BE_ASSERT(instance != nullptr);

            OnDestroy();
            delete instance;
            // instance = nullptr;
        };

        OnCreate = [&, instance]() {
            BE_ASSERT(instance != nullptr);

            instance->OnCreate();
            WasOnCreateCalled = true;
        };
        OnUpdate = [&, instance](f32 delta) {
            BE_ASSERT(instance != nullptr);

            instance->OnUpdate(delta);
        };
        OnDestroy = [&, instance]() {
            BE_ASSERT(instance != nullptr);

            instance->OnDestroy();
        };

        GetInstanceAsVoidPtr = [&, instance]() { return instance; };
        // };
    }

    // ScriptableEntity* Instance = nullptr;

    Script(const Script& other) = delete;
    Script(Script&& other) {
        // this->Instance = other.Instance;
        // this->Instantiate = other.Instantiate;
        this->DestroyInstance = other.DestroyInstance;
        this->OnCreate = other.OnCreate;
        this->OnUpdate = other.OnUpdate;
        this->OnDestroy = other.OnDestroy;
        this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;

        // other.Instantiate = nullptr;
        other.DestroyInstance = nullptr;
        other.OnCreate = nullptr;
        other.OnUpdate = nullptr;
        other.OnDestroy = nullptr;
        other.GetInstanceAsVoidPtr = nullptr;

        // other.Instance = nullptr;
    }
    Script& operator=(Script&& other) {
        if (this != &other) {
            // this->Instance = other.Instance;
            // this->Instantiate = other.Instantiate;
            this->DestroyInstance = other.DestroyInstance;
            this->OnCreate = other.OnCreate;
            this->OnUpdate = other.OnUpdate;
            this->OnDestroy = other.OnDestroy;
            this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;

            // other.Instantiate = nullptr;
            other.DestroyInstance = nullptr;
            other.OnCreate = nullptr;
            other.OnUpdate = nullptr;
            other.OnDestroy = nullptr;
            other.GetInstanceAsVoidPtr = nullptr;

            // other.Instance = nullptr;
        }
        return *this;
    }
    Script() = default;
};
}  // namespace Components
}  // namespace BillyEngine