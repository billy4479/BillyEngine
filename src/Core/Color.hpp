#pragma once

#include <glm/ext/vector_int3.hpp>
#include <glm/ext/vector_int4.hpp>
#include <glm/vec4.hpp>

#include "Core/Logger.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

struct Color {
    Color(glm::vec4);

    static Color FromRGBA(glm::ivec4);
    static Color FromRGBA(glm::ivec3);
    static Color FromU32(u32);

    glm::ivec4 ToRGBA() const;
    u32 ToU32() const;

    glm::vec4& Data();
    const glm::vec4& Data() const;

   private:
    glm::vec4 m_Data;
};

}  // namespace BillyEngine
