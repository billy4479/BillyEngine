#include "Rendering/Uniform.hpp"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "Core/Logger.hpp"

namespace BillyEngine {

#define SET_UNIFORM(type, ...) \
    glProgramUniform##type(m_Program, m_Location, __VA_ARGS__)

template <>
void Uniform<glm::vec4>::Set(const glm::vec4& v) {
    SET_UNIFORM(4f, v.x, v.y, v.z, v.w);
}

template <>
void Uniform<f32>::Set(const f32& v) {
    SET_UNIFORM(1f, v);
}

template <>
void Uniform<i32>::Set(const i32& v) {
    SET_UNIFORM(1i, v);
}

template <>
void Uniform<glm::mat4>::Set(const glm::mat4& v) {
    SET_UNIFORM(Matrix4fv, 1, GL_FALSE, glm::value_ptr(v));
}
}  // namespace BillyEngine