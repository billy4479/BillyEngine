#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
class Application;
class Entity {
   public:
    Entity(entt::entity handle, Application* application);
    Entity(const Entity& other) = default;

    ~Entity() = default;

    inline bool operator==(const Entity& other) {
        return this->m_Handle == other.m_Handle &&
               this->m_Application == other.m_Application;
    }
    inline bool operator!=(const Entity& other) { return !(*this == other); }
    inline operator bool() const { return m_Handle != entt::null; }
    inline operator entt::entity() const { return m_Handle; }
    inline operator u32() const { return (u32)m_Handle; }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    bool HasComponent();

    template <typename T>
    T& GetComponent();

   private:
    entt::entity m_Handle{entt::null};

   protected:
    Application* m_Application = nullptr;
};
}  // namespace BillyEngine