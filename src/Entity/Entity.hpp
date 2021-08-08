#pragma once

#include "../Core/Common.hpp"
#include "Component.hpp"

namespace Entity {
class Entity {
   public:
    Entity(std::vector<Entity>& reg) : Register(reg), id(++NextID) {
        Register.push_back(*this);
    }

    ~Entity() {
        for (size_t i = 0; i < Register.size(); i++) {
            if (Register[i].id == id) {
                Register.erase(Register.begin() + i);
                break;
            }
        }
    }

    template <typename T>
    void AddComponent(T&& component) {
        assert(!HasComponent<T>());
        Components.push_back(component);
    }

    template <typename T, typename... Args>
    void AddComponent(Args&&... args) {
        assert(!HasComponent<T>());
        Components.push_back(std::move(T(args...)));
    }

    template <typename T>
    void RemoveComponent() {
        assert(HasComponent<T>());
        for (size_t i = 0; i < Components.size(); i++) {
            assert(Components[i].has_value());
            if (Components[i].type() == typeid(T))
                Components.erase(Components.begin() + i);
        }
    }

    template <typename T>
    bool HasComponent() {
        for (auto c : Components) {
            assert(c.has_value());
            if (c.type() == typeid(T)) return true;
        }
        return false;
    }

    template <typename T>
    T* GetComponent() {
        assert(HasComponent<T>());
        for (auto c : Components) {
            assert(c.has_value());
            if (c.type() == typeid(T)) return std::any_cast<T>(&c);
        }
        return nullptr;
    }

    u32 GetId() { return id; }

   private:
    std::vector<Entity>& Register;
    std::vector<std::any> Components;
    const u32 id;
    static u32 NextID;

    // Entity(const Entity&);
};
}  // namespace Entity