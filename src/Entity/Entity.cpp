#include "Entity.hpp"

#include <any>
#include <cassert>
#include <vector>

#include "Component.hpp"

namespace Entity {

u32 Entity::NextID = 0;
std::vector<Entity*> Entity::Register = {};

Entity::Entity(const std::string& name) {
    id = ++NextID;
    Register.push_back(this);

    AddComponent<TagComponent>(name);
    AddComponent<TransformComponent>();
}

Entity::~Entity() {
    for (auto i = 0; i < Register.size(); i++) {
        if (Register[i]->id == id) {
            Register.erase(Register.begin() + i);
            break;
        }
    }
}

template <typename T, typename... Args>
void Entity::AddComponent(Args&&... args) {
    assert(!HasComponent<T>());
    Components.push_back(std::move(T(args...)));
}

template <typename T>
void Entity::RemoveComponent() {
    assert(HasComponent<T>());
    for (auto i = 0; i < Components.size(); i++) {
        assert(Components[i].has_value());
        if (Components[i].type() == typeid(T))
            Components.erase(Components.begin() + i);
    }
}

template <typename T>
bool Entity::HasComponent() {
    for (auto c : Components) {
        assert(c.has_value());
        if (c.type() == typeid(T)) return true;
    }
    return false;
}

template <typename T>
T& Entity::GetComponent() {
    assert(HasComponent<T>());
    for (auto c : Components) {
        assert(c.has_value());
        if (c.type() == typeid(T)) return std::any_cast<T>(&c);
    }
    return nullptr;
}

}  // namespace Entity
