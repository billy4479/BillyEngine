#include "Color.hpp"

#include "Common.hpp"

namespace BillyEngine {

Color Color::black(0, 0, 0);
Color Color::red(255, 0, 0);
Color Color::green(0, 255, 0);
Color Color::blue(0, 0, 255);
Color Color::white(255, 255, 255);

Color Color::hsl(u16 h, f32 s, f32 l, u8 a) {
    h = h % 360;
    BE_ASSERT(s <= 1 && s > 0);
    BE_ASSERT(l <= 1 && l > 0);

    // dbg_print("h: %u, s: %f, l: %f\n", h, s, l);

    f32 c = (1 - abs(2 * l - 1)) * s;
    f32 x = c * (1 - abs((f32)fmod(((f32)h / 60), 2) - 1));
    f32 m = l - c / 2;

    // dbg_print("c: %f, x: %f, m: %f\n", c, x, m);

    f32 r = 0, g = 0, b = 0;

    if (h < 60) {
        r = c;
        g = x;
    } else if (h < 120) {
        r = x;
        g = c;
    } else if (h < 180) {
        g = c;
        b = x;
    } else if (h < 240) {
        g = x;
        b = c;
    } else if (h < 300) {
        r = x;
        b = c;
    } else if (h <= 360) {
        r = c;
        b = x;
    } else {
        BE_ASSERT(false);
    }

    u8 R = (u8)((r + m) * 255);
    u8 G = (u8)((g + m) * 255);
    u8 B = (u8)((b + m) * 255);

    // dbg_print("R: %u, G: %u, B: %u\n", R, G, B);

    return Color(R, G, B, a);
}
}  // namespace BillyEngine