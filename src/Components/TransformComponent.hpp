#pragma once

#include "../Core/CenterPoint.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {

struct TransformComponent {
    glm::ivec2 Position;
    glm::vec2 Scale;
    f32 Rotation;
    CenterPoint Center;

    TransformComponent(glm::ivec2 position = {0, 0}, glm::vec2 scale = {1, 1},
                       f32 rotation = 0,
                       CenterPoint center = CenterPoint::TOP_LEFT)
        : Position(position),
          Scale(scale),
          Rotation(rotation),
          Center(center) {}

    TransformComponent(const TransformComponent&) = delete;

    TransformComponent(TransformComponent&& other) noexcept {
        this->Position = other.Position;
        this->Rotation = other.Rotation;
        this->Scale = other.Scale;
        this->Center = other.Center;
    }

    TransformComponent& operator=(TransformComponent&& other) noexcept {
        if (this != &other) {
            this->Position = other.Position;
            this->Rotation = other.Rotation;
            this->Scale = other.Scale;
            this->Center = other.Center;
        }

        return *this;
    }
};

}  // namespace Components
}  // namespace BillyEngine