#pragma once

#include "../Core/CenterPoint.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {

struct TransformComponent {
    glm::ivec2 Position;
    glm::vec2 Scale;
    f32 Rotation;
    CenterPoint RotationCenter;
    CenterPoint Anchor;

    TransformComponent(glm::ivec2 position = {0, 0}, glm::vec2 scale = {1, 1},
                       f32 rotation = 0,
                       CenterPoint rotationCenter = CenterPoint::CENTER_CENTER,
                       CenterPoint anchor = CenterPoint::TOP_LEFT)
        : Position(position),
          Scale(scale),
          Rotation(rotation),
          RotationCenter(rotationCenter),
          Anchor(anchor) {}

    TransformComponent(const TransformComponent&) = delete;

    TransformComponent(TransformComponent&& other) noexcept {
        this->Position = other.Position;
        this->Rotation = other.Rotation;
        this->Scale = other.Scale;
        this->RotationCenter = other.RotationCenter;
        this->Anchor = other.Anchor;
    }

    TransformComponent& operator=(TransformComponent&& other) noexcept {
        if (this != &other) {
            this->Position = other.Position;
            this->Rotation = other.Rotation;
            this->Scale = other.Scale;
            this->RotationCenter = other.RotationCenter;
            this->Anchor = other.Anchor;
        }

        return *this;
    }
};

}  // namespace Components
}  // namespace BillyEngine