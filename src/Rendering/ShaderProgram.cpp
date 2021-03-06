#include "Rendering/ShaderProgram.hpp"

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
    BE_LOG_GL_CALL("glCreateProgram() -> {}", m_Program);

    BE_LOG_GL_CALL("glAttach({}, {})", m_Program, vertexShader->GetID());
    glAttachShader(m_Program, vertexShader->GetID());
    BE_LOG_GL_CALL("glAttach({}, {})", m_Program, fragmentShader->GetID());
    glAttachShader(m_Program, fragmentShader->GetID());
    BE_LOG_GL_CALL("glLinkProgram({})", m_Program);
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
    BE_LOG_GL_CALL("glDeleteProgram({})", m_Program);
    glDeleteProgram(m_Program);
}

u32 ShaderProgram::GetID() const { return m_Program; }

void ShaderProgram::Use() const {
    BE_LOG_GL_CALL("glUseProgram({})", m_Program);
    glUseProgram(m_Program);
}

i32 ShaderProgram::GetUniformFromShader(std::string_view name) const {
    auto location = glGetUniformLocation(m_Program, name.data());
    BE_LOG_GL_CALL("glGetUniformLocation({}, {}) -> {}", m_Program, name,
                   location);

    if (location == -1) Logger::Core()->error("Uniform \"{}\" not found", name);
    return location;
}

i32 ShaderProgram::GetUniformAndCheck(std::string_view name) {
    auto result = m_UniformCache.find(name);
    if (result == m_UniformCache.end()) {
        auto uniform = GetUniformFromShader(name);
        m_UniformCache[name] = uniform;
        return uniform;
    }

    return result->second;
}

}  // namespace BillyEngine