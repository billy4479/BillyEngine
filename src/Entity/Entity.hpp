#pragma once

#include "../Core/Common.hpp"
#include "Component.hpp"

namespace Entity {
class Register;
class Entity {
   public:
    ~Entity();

    explicit inline operator u32() { return id; }
    inline bool operator==(const Entity& other) { return this->id == other.id; }
    inline bool operator!=(const Entity& other) { return !(*this == other); }

    template <typename T>
    inline void AddComponent(T&&);

    template <typename T, typename... Args>
    inline void AddComponent(Args&&...);

    template <typename T>
    inline void RemoveComponent();

    template <typename T>
    inline bool HasComponent();

    template <typename T>
    inline T& GetComponent();

    inline u32 GetId() const { return id; }

   private:
    const u32 id;
    Register& m_Reg;

    Entity(u32 id, Register& reg) : id(id), m_Reg(reg) {}

    friend class Register;
};
}  // namespace Entity