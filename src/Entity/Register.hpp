#pragma once

#include "../Core/Common.hpp"

class Application;
namespace Entity {

class Entity;
class Register {
   public:
    Register() = default;
    ~Register() = default;

    Entity CreateEntity();

    Entity GetEntityByID(u32);

    template <typename T>
    T& GetComponent(const Entity&);

    template <typename T, typename... Args>
    void AddComponent(Entity&, Args&&...);

    template <typename T>
    void AddComponent(Entity& entity, T&& component);

    template <typename T>
    void RemoveComponent(Entity&);

    template <typename T>
    bool HasComponent(const Entity&);

   private:
    using m_RegisterPair = std::pair<const Entity, std::vector<std::any>>;

    m_RegisterPair& GetPair(const Entity&);
    void UnregisterEntity(const Entity&);
    std::map<Entity, std::vector<std::any>>& GetReg() { return m_Register; }

    static u32 NextID;
    std::map<Entity, std::vector<std::any>> m_Register;
    friend class Entity;
    friend class ::Application;
};

}  // namespace Entity

// #include "Register.inl"