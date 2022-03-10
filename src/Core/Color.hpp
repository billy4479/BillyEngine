#pragma once

#include <glm/vec4.hpp>

#include "Types.hpp"

namespace BillyEngine {

using Color = glm::vec4;
Color ColorFromBytes(u8 r, u8 g, u8 b, u8 a = 0xff);

}  // namespace BillyEngine