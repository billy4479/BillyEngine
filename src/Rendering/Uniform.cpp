#include "Uniform.hpp"

#include <glad/gl.h>

#include <glm/vec4.hpp>

#include "Core/Logger.hpp"

namespace BillyEngine {

template <>
void Uniform<glm::vec4>::Set(const glm::vec4& v) {
    glUniform4f(m_Location, v.x, v.y, v.z, v.w);
}

template <>
void Uniform<f32>::Set(const f32& v) {
    glUniform1f(m_Location, v);
}

}  // namespace BillyEngine