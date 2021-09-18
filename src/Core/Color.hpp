/**
 * @file Color.hpp
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <spdlog/formatter.h>

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
     * @brief Convert to RGBA32
     *
     * @return The result unsigned int
     */
    inline operator u32() const {
        u32 res = ((u32)r << 24) | ((u32)g << 16) | ((u32)b << 8) | a;
        // dbg_print("#%X\n", res);
        return res;
    }
    inline operator SDL_Color() const { return SDL_Color{r, g, b, a}; }

    u8 r = 0, g = 0, b = 0, a = 0xff;

    /**
     * @brief The pixelformat to be used in textures
     *
     * If changed also the `u32()` operator has to be adapted.
     *
     */
    static constexpr u32 PixelFormat = SDL_PIXELFORMAT_RGBA8888;

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

// https://fmt.dev/latest/api.html#format-api
template <>
struct fmt::formatter<BillyEngine::Color> {
    char presentation = 'd';
    bool useHashTag = false;

    static constexpr std::string_view xHash =
        "(R: {:#04x}, G: {:#04x}, B: {:#04x}, A: {:#04x})";
    static constexpr std::string_view XHash =
        "(R: {:#04X}, G: {:#04X}, B: {:#04X}, A: {:#04X})";
    static constexpr std::string_view d =
        "(R: {:d}, G: {:d}, B: {:d}, A: {:d})";
    static constexpr std::string_view x =
        "(R: {:x}, G: {:x}, B: {:x}, A: {:x})";
    static constexpr std::string_view X =
        "(R: {:X}, G: {:X}, B: {:X}, A: {:X})";

    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it == '#') {
            useHashTag = true;
            it++;
        }

        if (it != end && (*it == 'd' || *it == 'x' || *it == 'X')) {
            if (useHashTag && *it == 'd') throw format_error("invalid format");

            presentation = *it++;
        }

        if (it != end && *it != '}') throw format_error("invalid format");

        return it;
    }

    template <typename FormatCtx>
    auto format(const BillyEngine::Color& c, FormatCtx& ctx)
        -> decltype(ctx.out()) {
        if (useHashTag) {
            switch (presentation) {
                case 'x':
                    return format_to(ctx.out(), xHash, c.r, c.g, c.b, c.a);
                case 'X':
                default:
                    return format_to(ctx.out(), XHash, c.r, c.g, c.b, c.a);
            }
        } else {
            switch (presentation) {
                case 'x':
                    return format_to(ctx.out(), x, c.r, c.g, c.b, c.a);
                case 'X':
                    return format_to(ctx.out(), X, c.r, c.g, c.b, c.a);
                case 'd':
                default:
                    return format_to(ctx.out(), d, c.r, c.g, c.b, c.a);
            }
        }
    }
};