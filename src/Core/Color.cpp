#include "Color.hpp"

namespace BillyEngine {

Color ColorFromBytes(u8 r, u8 g, u8 b, u8 a) {
    Color c;

    c.r = (f32)r / 0xff;
    c.g = (f32)g / 0xff;
    c.b = (f32)b / 0xff;
    c.a = (f32)a / 0xff;

    return c;
}

}  // namespace BillyEngine