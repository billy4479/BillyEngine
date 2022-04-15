#pragma once

#include <spdlog/spdlog.h>

#include <glm/ext/vector_int3.hpp>
#include <glm/ext/vector_int4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Core/Color.hpp"

// https://fmt.dev/latest/api.html#format-api
template <>
struct fmt::formatter<BillyEngine::Color> {
    char presentation = 'x';
    bool useHashTag = true;

    static constexpr std::string_view xHash = "#{:08x}";
    static constexpr std::string_view XHash = "#{:08X}";
    static constexpr std::string_view x = "{:08x}";
    static constexpr std::string_view X = "{:08X}";

    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it == '#') {
            useHashTag = true;
            it++;
        } else {
            useHashTag = false;
        }

        if (it != end && (*it == 'd' || *it == 'x' || *it == 'X')) {
            if (useHashTag && *it == 'd') BillyEngine::VERIFY_NOT_REACHED();

            presentation = *it++;
        }

        if (it != end && *it != '}') BillyEngine::VERIFY_NOT_REACHED();

        return it;
    }

    template <typename FormatCtx>
    auto format(const BillyEngine::Color& c, FormatCtx& ctx)
        -> decltype(ctx.out()) {
        if (useHashTag) {
            switch (presentation) {
                case 'x':
                    return format_to(ctx.out(), xHash, c.ToU32());
                case 'X':
                default:
                    return format_to(ctx.out(), XHash, c.ToU32());
            }
        } else {
            switch (presentation) {
                case 'x':
                    return format_to(ctx.out(), x, c.ToU32());
                case 'X':
                    return format_to(ctx.out(), X, c.ToU32());
                case 'd':
                default:
                    return format_to(ctx.out(), "{}", c.ToRGBA());
            }
        }
    }
};

template <>
struct fmt::formatter<glm::vec2> : fmt::formatter<float> {
    template <typename FormatCtx>
    auto format(const glm::vec2& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<float>::format(v.x, ctx);
        format_to(ctx.out(), ",");
        formatter<float>::format(v.y, ctx);
        format_to(ctx.out(), ")");
        return ctx.out();
    }
};

template <>
struct fmt::formatter<glm::ivec4> : fmt::formatter<int> {
    template <typename FormatCtx>
    auto format(const glm::ivec4& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<int>::format(v.r, ctx);
        format_to(ctx.out(), ",");
        formatter<int>::format(v.g, ctx);
        format_to(ctx.out(), ",");
        formatter<int>::format(v.b, ctx);
        format_to(ctx.out(), ",");
        formatter<int>::format(v.a, ctx);
        format_to(ctx.out(), ")");
        return ctx.out();
    }
};

template <>
struct fmt::formatter<glm::ivec3> : fmt::formatter<int> {
    template <typename FormatCtx>
    auto format(const glm::ivec3& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<int>::format(v.r, ctx);
        format_to(ctx.out(), ",");
        formatter<int>::format(v.g, ctx);
        format_to(ctx.out(), ",");
        formatter<int>::format(v.b, ctx);
        format_to(ctx.out(), ",");
        return ctx.out();
    }
};

template <>
struct fmt::formatter<glm::vec4> : fmt::formatter<float> {
    template <typename FormatCtx>
    auto format(const glm::vec4& v, FormatCtx& ctx) {
        format_to(ctx.out(), "(");
        formatter<float>::format(v.r, ctx);
        format_to(ctx.out(), ",");
        formatter<float>::format(v.g, ctx);
        format_to(ctx.out(), ",");
        formatter<float>::format(v.b, ctx);
        format_to(ctx.out(), ",");
        formatter<float>::format(v.a, ctx);
        format_to(ctx.out(), ")");
        return ctx.out();
    }
};