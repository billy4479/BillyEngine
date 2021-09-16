#include "TransformComponent.hpp"

namespace BillyEngine {
namespace Components {
Transform::Transform(glm::ivec2 position, glm::vec2 scale, f32 rotation,
                     CenterPoint rotationCenter, CenterPoint anchor)
    : Position(position),
      Scale(scale),
      Rotation(rotation),
      RotationCenter(rotationCenter),
      Anchor(anchor) {}
}  // namespace Components
}  // namespace BillyEngine