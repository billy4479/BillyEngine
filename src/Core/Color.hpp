#pragma once

#include "Common.hpp"

namespace BillyEngine {

struct Color {
   public:
    Color() = default;
    Color(u8 r, u8 g, u8 b, u8 a = 0xff) : r(r), g(g), b(b), a(a) {}
    inline operator u32() const { return (b << 24) | (g << 16) | (r << 8) | a; }
    inline operator SDL_Color() const { return SDL_Color{r, g, b, a}; }

    u8 r = 0, g = 0, b = 0, a = 0xff;

    static Color red;
    static Color blue;
    static Color green;
    static Color black;
    static Color white;

    static Color hsl(u16 h, f32 s, f32 l, u8 a = 0xff);
};
}  // namespace BillyEngine