/**
 * @file Color.hpp
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include "Common.hpp"

namespace BillyEngine {

/**
 * @brief A simple RGBA8 color struct
 *
 */
struct Color {
   public:
    Color() = default;
    /**
     * @brief Create a new color from RGBA values
     *
     * @param r Red channel
     * @param g Green channel
     * @param b Blue channel
     * @param a Alpha channel, defaulted to `0xff`
     */
    Color(u8 r, u8 g, u8 b, u8 a = 0xff) : r(r), g(g), b(b), a(a) {}
    /**
     * @brief Convert to BGRA32
     *
     * @return The result unsigned int
     */
    inline operator u32() const { return (b << 24) | (g << 16) | (r << 8) | a; }
    inline operator SDL_Color() const { return SDL_Color{r, g, b, a}; }

    u8 r = 0, g = 0, b = 0, a = 0xff;

    /**
     * @brief The pixelformat to be used in textures
     *
     * If changed also the `u32()` operator has to be adapted.
     *
     */
    static constexpr u32 PixelFormat = SDL_PIXELFORMAT_BGRA32;

    static Color red;
    static Color blue;
    static Color green;
    static Color black;
    static Color white;

    /**
     * @brief Create a new color from HSL
     *
     * @param h Hue
     * @param s Saturation
     * @param l Luminance
     * @param a Alpha channel, defaulted to `0xff`
     * @return Color
     */
    static Color hsl(u16 h, f32 s, f32 l, u8 a = 0xff);
};
}  // namespace BillyEngine