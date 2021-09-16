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

    Transform(glm::ivec2 position = {0, 0}, glm::vec2 scale = {1, 1},
              f32 rotation = 0,
              CenterPoint rotationCenter = CenterPoint::CENTER_CENTER,
              CenterPoint anchor = CenterPoint::TOP_LEFT);
};

}  // namespace Components
}  // namespace BillyEngine