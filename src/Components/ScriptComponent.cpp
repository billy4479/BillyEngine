#include "ScriptComponent.hpp"

namespace BillyEngine {
namespace Components {
Script::Script() = default;

#ifdef DEBUG
    #define REPLACER(...) [](__VA_ARGS__) { BE_ABORT(); }
#else
    #define REPLACER(...) nullptr
#endif

Script::Script(Script&& other) noexcept {
    this->DestroyInstance = other.DestroyInstance;
    this->OnCreate = other.OnCreate;
    this->OnUpdate = other.OnUpdate;
    this->OnDestroy = other.OnDestroy;
    this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;
    this->WasOnCreateCalled = other.WasOnCreateCalled;

    other.DestroyInstance = REPLACER(Script*);
    other.OnCreate = REPLACER(Script*);
    other.OnUpdate = REPLACER(Script*, f32);
    other.OnDestroy = REPLACER(Script*);
    other.GetInstanceAsVoidPtr = [] { return nullptr; };
    other.WasOnCreateCalled = false;
}

Script::~Script() {
    if (GetInstanceAsVoidPtr() != nullptr) DestroyInstance(this);
}
Script& Script::operator=(Script&& other) noexcept {
    if (this != &other) {
        this->DestroyInstance = other.DestroyInstance;
        this->OnCreate = other.OnCreate;
        this->OnUpdate = other.OnUpdate;
        this->OnDestroy = other.OnDestroy;
        this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;
        this->WasOnCreateCalled = other.WasOnCreateCalled;

        other.DestroyInstance = REPLACER(Script*);
        other.OnCreate = REPLACER(Script*);
        other.OnUpdate = REPLACER(Script*, f32);
        other.OnDestroy = REPLACER(Script*);
        other.GetInstanceAsVoidPtr = [] { return nullptr; };
        other.WasOnCreateCalled = false;
    }
    return *this;
}
}  // namespace Components
}  // namespace BillyEngine