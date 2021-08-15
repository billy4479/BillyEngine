#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {

struct TransformComponent {
    std::pair<i32, i32> Position = {0, 0};
    std::pair<f32, f32> Scale = {1, 1};
    f32 Rotation = 0;

    TransformComponent(std::pair<i32, i32> position, std::pair<f32, f32> scale,
                       f32 rotation)
        : Position(position), Scale(scale), Rotation(rotation) {}

    TransformComponent() = default;

    TransformComponent(const TransformComponent&) = delete;

    TransformComponent(TransformComponent&& other) noexcept {
        this->Position = other.Position;
        this->Rotation = other.Rotation;
        this->Scale = other.Scale;
    }

    TransformComponent& operator=(TransformComponent&& other) noexcept {
        if (this != &other) {
            this->Position = other.Position;
            this->Rotation = other.Rotation;
            this->Scale = other.Scale;
        }

        return *this;
    }
};

}  // namespace Components
}  // namespace BillyEngine