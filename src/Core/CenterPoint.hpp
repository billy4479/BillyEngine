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

[[maybe_unused]] inline static const glm::ivec2 CenterPointToCoords(
    const CenterPoint& center, SDL_Rect& dRect) {
    switch (center) {
        case CenterPoint::TOP_LEFT:
            return {0, 0};
            break;
        case CenterPoint::TOP_CENTER:
            return {dRect.w / 2, 0};
            break;
        case CenterPoint::TOP_RIGHT:
            return {dRect.w, 0};
            break;
        case CenterPoint::CENTER_LEFT:
            return {0, dRect.h / 2};
            break;
        case CenterPoint::CENTER_CENTER:
            return {dRect.w / 2, dRect.h / 2};
            break;
        case CenterPoint::CENTER_RIGHT:
            return {dRect.w, dRect.h / 2};
            break;
        case CenterPoint::BOTTOM_LEFT:
            return {0, dRect.h};
            break;
        case CenterPoint::BOTTOM_CENTER:
            return {dRect.w / 2, dRect.h};
            break;
        case CenterPoint::BOTTOM_RIGHT:
            return {dRect.w, dRect.h};
            break;
    }

    return {0, 0};
}

// static const SDL_Point CenterPointToCoords(const CenterPoint& center,
//                                            SDL_Rect& dRect) {
//     glm::ivec2 v = CenterPointToCoords(center, dRect);
//     return {v.x, v.y};
// }

}  // namespace BillyEngine