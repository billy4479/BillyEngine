#pragma once

#include "Common.hpp"

namespace BillyEngine {

enum class CenterPoint {
    TOP_RIGHT,
    TOP_CENTER,
    TOP_LEFT,
    CENTER_RIGHT,
    CENTER_CENTER,
    CENTER_LEFT,
    BOTTOM_RIGHT,
    BOTTOM_CENTER,
    BOTTOM_LEFT,
};

const glm::ivec2 CenterPointToCoords(const CenterPoint& center,
                                     SDL_Rect& dRect);

}  // namespace BillyEngine