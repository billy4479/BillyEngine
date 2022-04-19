#include "ShaderProgram.hpp"

#include <glad/gl.h>

#include <glm/vec4.hpp>

#include "Core/Logger.hpp"
#include "Rendering/Shader.hpp"

namespace BillyEngine {
Ref<ShaderProgram> ShaderProgram::Create(const Ref<Shader> vertexShader,
                                         const Ref<Shader> fragmentShader) {
    return Ref<ShaderProgram>(new ShaderProgram(vertexShader, fragmentShader));
}

ShaderProgram::ShaderProgram(const Ref<Shader> vertexShader,
                             const Ref<Shader> fragmentShader) {
    m_Program = glCreateProgram();
    BE_GL_LOG("glCreateProgram() -> {}", m_Program);

    BE_GL_LOG("glAttach({}, {})", m_Program, vertexShader->GetID());
    glAttachShader(m_Program, vertexShader->GetID());
    BE_GL_LOG("glAttach({}, {})", m_Program, fragmentShader->GetID());
    glAttachShader(m_Program, fragmentShader->GetID());
    BE_GL_LOG("glLinkProgram({})", m_Program);
    glLinkProgram(m_Program);

    i32 success;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);

    if (!success) {
        char buffer[512];
        glGetProgramInfoLog(m_Program, sizeof(buffer), nullptr, buffer);
        Logger::Core()->error("Error while linking shaders: {}", buffer);

        glDeleteProgram(m_Program);
        m_Program = 0;
        return;
    }
}

ShaderProgram::~ShaderProgram() {
    BE_GL_LOG("glDeleteProgram({})", m_Program);
    glDeleteProgram(m_Program);
}

u32 ShaderProgram::GetID() const { return m_Program; }

void ShaderProgram::Use() const {
    BE_GL_LOG("glUseProgram({})", m_Program);
    glUseProgram(m_Program);
}

i32 ShaderProgram::GetUniformAndCheck(std::string_view name) {
    auto location = glGetUniformLocation(m_Program, name.data());
    BE_GL_LOG("glGetUniformLocation({}, {}) -> {}", m_Program, name, location);
    if (location == -1) {
        Logger::Core()->error("Uniform \"{}\" not found", name);
    }
    return location;
}

}  // namespace BillyEngine