#include "ScriptComponent.hpp"

namespace BillyEngine {
namespace Components {
Script::Script() = default;

Script::Script(Script&& other) noexcept {
    this->DestroyInstance = other.DestroyInstance;
    this->OnCreate = other.OnCreate;
    this->OnUpdate = other.OnUpdate;
    this->OnDestroy = other.OnDestroy;
    this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;

    other.DestroyInstance = nullptr;
    other.OnCreate = nullptr;
    other.OnUpdate = nullptr;
    other.OnDestroy = nullptr;
    other.GetInstanceAsVoidPtr = nullptr;
}

Script::~Script() { DestroyInstance(); }
Script& Script::operator=(Script&& other) noexcept {
    if (this != &other) {
        this->DestroyInstance = other.DestroyInstance;
        this->OnCreate = other.OnCreate;
        this->OnUpdate = other.OnUpdate;
        this->OnDestroy = other.OnDestroy;
        this->GetInstanceAsVoidPtr = other.GetInstanceAsVoidPtr;

        other.DestroyInstance = nullptr;
        other.OnCreate = nullptr;
        other.OnUpdate = nullptr;
        other.OnDestroy = nullptr;
        other.GetInstanceAsVoidPtr = nullptr;
    }
    return *this;
}
}  // namespace Components
}  // namespace BillyEngine