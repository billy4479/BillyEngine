#include "CenterPoint.hpp"

namespace BillyEngine {
const glm::ivec2 CenterPointToCoords(const CenterPoint& center,
                                     SDL_Rect& dRect) {
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
}  // namespace BillyEngine