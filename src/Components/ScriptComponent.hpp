#pragma once

#include "../Core/Common.hpp"
#include "../Entity/Entity.hpp"
#include "IDComponent.hpp"

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

class Script {
   public:
    template <EntityScriptClass T>
    inline T* GetInstanceOrFail() {
        if (GetInstanceAsVoidPtr() == nullptr) {
            BE_ABORT();
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

        instance = new T(e, std::forward<Args>(args)...);
        BE_ASSERT(instance != nullptr);

        DestroyInstance = [instance](Script* f_This) {
            BE_ASSERT(instance != nullptr);

            f_This->OnDestroy(f_This);
            delete instance;
        };

        OnCreate = [instance](Script* f_This) {
            BE_ASSERT(instance != nullptr);

            instance->OnCreate();
            f_This->WasOnCreateCalled = true;
        };
        OnUpdate = [instance](Script*, f32 delta) {
            BE_ASSERT(instance != nullptr);

            instance->OnUpdate(delta);
        };
        OnDestroy = [instance](Script*) {
            BE_ASSERT(instance != nullptr);

            instance->OnDestroy();
        };

        GetInstanceAsVoidPtr = [instance] { return instance; };
    }

    Script();
    ~Script();

    BE_NON_COPY_CONSTRUCTIBLE(Script)

    Script(Script&& other) noexcept;
    Script& operator=(Script&& other) noexcept;

   private:
    std::function<void(Script*)> DestroyInstance;

    std::function<void(Script*)> OnCreate;
    std::function<void(Script*, f32)> OnUpdate;
    std::function<void(Script*)> OnDestroy;

    std::function<void*()> GetInstanceAsVoidPtr = []() { return nullptr; };

    bool WasOnCreateCalled = false;

    friend class ::BillyEngine::EntityManager;
    friend class ::BillyEngine::Application;
};
}  // namespace Components
}  // namespace BillyEngine

#undef EntityScriptClass