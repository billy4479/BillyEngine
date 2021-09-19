#pragma once

#include "Aliases.hpp"
#include "Color.hpp"
#include "STDInclude.hpp"

// https://fmt.dev/latest/api.html#format-api
template <>
struct fmt::formatter<BillyEngine::Color> {
    char presentation = 'd';
    bool useHashTag = false;

    static constexpr std::string_view xHash = "{:#010x}";
    static constexpr std::string_view XHash = "{:#010X}";
    static constexpr std::string_view x = "{:010x}";
    static constexpr std::string_view X = "{:010X}";
    static constexpr std::string_view d =
        "(R: {:d}, G: {:d}, B: {:d}, A: {:d})";

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
                    return format_to(ctx.out(), xHash, (u32)c);
                case 'X':
                default:
                    return format_to(ctx.out(), XHash, (u32)c);
            }
        } else {
            switch (presentation) {
                case 'x':
                    return format_to(ctx.out(), x, (u32)c);
                case 'X':
                    return format_to(ctx.out(), X, (u32)c);
                case 'd':
                default:
                    return format_to(ctx.out(), d, (u32)c);
            }
        }
    }
};

template <>
struct fmt::formatter<glm::vec2> : fmt::formatter<f32> {
    template <typename FormatCtx>
    auto format(const glm::vec2& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<f32>::format(v.x, ctx);
        format_to(ctx.out(), ",");
        formatter<f32>::format(v.y, ctx);
        format_to(ctx.out(), ")");
        return ctx.out();
    }
};

template <>
struct fmt::formatter<glm::ivec2> : fmt::formatter<i32> {
    template <typename FormatCtx>
    auto format(const glm::ivec2& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<i32>::format(v.x, ctx);
        format_to(ctx.out(), ",");
        formatter<i32>::format(v.y, ctx);
        format_to(ctx.out(), ")");
        return ctx.out();
    }
};