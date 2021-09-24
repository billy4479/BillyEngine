#pragma once

#include "../Core/CenterPoint.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {

class Transform {
   public:
    glm::ivec2 Position;
    glm::vec2 Scale;
    f32 Rotation;
    CenterPoint RotationCenter;
    CenterPoint Anchor;
    i32 zIndex;

    Transform(glm::ivec2 position = {0, 0}, glm::vec2 scale = {1, 1},
              f32 rotation = 0,
              CenterPoint rotationCenter = CenterPoint::CENTER_CENTER,
              CenterPoint anchor = CenterPoint::TOP_LEFT, i32 zIndex = 0);
};

}  // namespace Components
}  // namespace BillyEngine