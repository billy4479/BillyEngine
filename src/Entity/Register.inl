#pragma once

#include "Entity.hpp"
#include "Register.hpp"

namespace Entity {

Entity Register::CreateEntity() { return Entity(++NextID, *this); }

u32 Register::NextID = 0;

Entity Register::GetEntityByID(u32 id) {
    return GetPair(Entity(id, *this)).first;
}

template <typename T>
T& Register::GetComponent(const Entity& entity) {
    assert(HasComponent<T>(entity));
    auto p = GetPair(entity);
    for (auto c : p.second) {
        assert(c.has_value());
        if (c.type() == typeid(T)) {
            return std::any_cast<T>(c);
        }
    }
    assert(false);
}

template <typename T, typename... Args>
void Register::AddComponent(Entity& entity, Args&&... args) {
    GetPair(entity).second.push_back(std::move(T(std::forward(args...))));
}

template <typename T>
void Register::AddComponent(Entity& entity, T&& component) {
    GetPair(entity).second.push_back(std::move(component));
}

template <typename T>
void Register::RemoveComponent(Entity& entity) {
    assert(HasComponent<T>(entity));
    auto p = GetPair(entity);
    for (size_t i = 0; i < p.second.size(); i++) {
        assert(p.second[i].has_value());
        if (p.second[i].type() == typeid(T)) {
            p.second.erase(p.second.begin() + i);
            return;
        }
    }
}

template <typename T>
bool Register::HasComponent(const Entity& entity) {
    auto p = GetPair(entity);
    for (auto c : p.second) {
        assert(c.has_value());
        if (c.type() == typeid(T)) {
            return true;
        }
    }
    return false;
}

Register::m_RegisterPair& Register::GetPair(const Entity& entity) {
    for (auto& e : m_Register) {
        if (e.first.id == entity.GetId()) return e;
    }
    assert(false);
}

void Register::UnregisterEntity(const Entity& entity) {
    for (auto it = m_Register.begin(); it != m_Register.end(); ++it) {
        if (it->first.GetId() == entity.GetId()) {
            m_Register.erase(it);
            return;
        }
    }
}

}  // namespace Entity
