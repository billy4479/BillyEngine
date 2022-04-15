#include "Color.hpp"

namespace BillyEngine {

Color::Color(glm::vec4 data) : m_Data(data) {}

Color Color::FromRGBA(glm::ivec4 c) {
    return glm::vec4{
        (f32)c.r / 0xff,
        (f32)c.g / 0xff,
        (f32)c.b / 0xff,
        (f32)c.a / 0xff,
    };
}

Color Color::FromRGBA(glm::ivec3 c) {
    return glm::vec4{
        (f32)c.r / 0xff,
        (f32)c.g / 0xff,
        (f32)c.b / 0xff,
        1,
    };
}

Color Color::FromU32(u32 c) {
    // UH magic!
    return FromRGBA({
        (c & (0xff << (6 * 4))) >> (6 * 4),
        (c & (0xff << (4 * 4))) >> (4 * 4),
        (c & (0xff << (2 * 4))) >> (2 * 4),
        (c & (0xff << (0 * 4))) >> (0 * 4),
    });
}

glm::ivec4 Color::ToRGBA() const {
    return glm::ivec4{
        m_Data.r * 0xff,
        m_Data.g * 0xff,
        m_Data.b * 0xff,
        m_Data.a * 0xff,
    };
}

u32 Color::ToU32() const {
    const auto c = ToRGBA();
    return (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
}

glm::vec4 &Color::Data() { return m_Data; }
const glm::vec4 &Color::Data() const { return m_Data; }

}  // namespace BillyEngine