#include "Shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>

#include "Core/Logger.hpp"

namespace BillyEngine {

AssetType Shader::GetAssetTypeStatic() { return AssetType::Shader; }
AssetType Shader::GetAssetType() { return GetAssetTypeStatic(); }

static std::string LoadShaderSource(std::filesystem::path path) {
    std::fstream file;
    file.open(path);
    if (!file.is_open())
        Logger::Core()->error("Error loading shader at {}", path.string());

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Ref<Shader> Shader::Load(std::filesystem::path path, ShaderType type) {
    return Load((std::string_view)LoadShaderSource(path), type);
}

Ref<Shader> Shader::Load(std::string_view src, ShaderType type) {
    return CreateRef<Shader>(src, type);
}

Shader::~Shader() {}

static std::string_view GetShaderName(Shader::ShaderType type) {
    switch (type) {
        case Shader::ShaderType::Vertex:
            return "vertex";
        case Shader::ShaderType::Fragment:
            return "fragment";
    }

    return "";
}

Shader::Shader(std::string_view source, ShaderType type) : m_Type(type) {
    switch (m_Type) {
        case ShaderType::Vertex:
            m_Shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::Fragment:
            m_Shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }

    auto s = source.data();
    glShaderSource(m_Shader, 1, &s, nullptr);
    glCompileShader(m_Shader);

    i32 success;
    glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char buffer[512];
        glGetShaderInfoLog(m_Shader, sizeof(buffer), nullptr, buffer);
        Logger::Core()->error("Error compiling {} shader: {}",
                              GetShaderName(m_Type), buffer);
    }
}

}  // namespace BillyEngine