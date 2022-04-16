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
    glAttachShader(m_Program, vertexShader->GetID());
    glAttachShader(m_Program, fragmentShader->GetID());
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

ShaderProgram::~ShaderProgram() { glDeleteProgram(m_Program); }

u32 ShaderProgram::GetID() const { return m_Program; }

void ShaderProgram::Use() const { glUseProgram(m_Program); }

i32 ShaderProgram::GetUniformAndCheck(std::string_view name) {
    auto location = glGetUniformLocation(m_Program, name.data());
    if (location == -1) {
        Logger::Core()->error("Uniform \"{}\" not found", name);
    }
    return location;
}

}  // namespace BillyEngine