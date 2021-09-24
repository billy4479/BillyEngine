#include "TransformComponent.hpp"

namespace BillyEngine {
namespace Components {
Transform::Transform(glm::ivec2 position, glm::vec2 scale, f32 rotation,
                     CenterPoint rotationCenter, CenterPoint anchor, i32 zIndex)
    : Position(position),
      Scale(scale),
      Rotation(rotation),
      RotationCenter(rotationCenter),
      Anchor(anchor),
      zIndex(zIndex) {}
}  // namespace Components
}  // namespace BillyEngine