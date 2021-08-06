#pragma once
#include <any>
#include <string>
#include <vector>

#include "../Core/Common.hpp"

namespace Entity {
class Entity {
   public:
    Entity(const std::string&);
    ~Entity();

    u32 id = 0;

    template <typename T, typename... Args>
    void AddComponent(Args&&... args);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    bool HasComponent();

    template <typename T>
    T& GetComponent();

    std::vector<std::any> Components;

    static std::vector<Entity*> Register;
    static u32 NextID;
};
}  // namespace Entity