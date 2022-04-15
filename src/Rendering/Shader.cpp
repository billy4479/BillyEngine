#include "Shader.hpp"

#include <glad/gl.h>

#include <fstream>
#include <sstream>
#include <string>

#include "Core/Logger.hpp"

namespace BillyEngine {

AssetType Shader::GetAssetTypeStatic() { return AssetType::Shader; }
AssetType Shader::GetAssetType() const { return GetAssetTypeStatic(); }

static std::string_view GetShaderName(Shader::ShaderType type) {
    switch (type) {
        case Shader::ShaderType::Vertex:
            return "vertex";
        case Shader::ShaderType::Fragment:
            return "fragment";
    }

    return "";
}

static std::string LoadShaderSource(std::filesystem::path path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open())
        Logger::Core()->error("Error loading shader at {}", path.string());

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    return ss.str();
}

Ref<Shader> Shader::Load(std::filesystem::path path, ShaderType type) {
    return Load((std::string_view)LoadShaderSource(path), type);
}

Ref<Shader> Shader::Load(std::string_view src, ShaderType type) {
    return Ref<Shader>(new Shader(src, type));
}

u32 Shader::GetID() const { return m_Shader; }

Shader::~Shader() {
    glDeleteShader(m_Shader);
    // Logger::Core()->debug("Deleted {} shader", GetShaderName(m_Type));
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

        glDeleteShader(m_Shader);
        m_Shader = 0;
        return;
    }

#if 0
    Logger::Core()->debug("{} shader created successfully",
                          GetShaderName(type));
    {
        std::string buffer;
        std::stringstream ss(src.data());

        while (std::getline(ss, buffer, '\n'))
            Logger::Core()->debug("\t{}", buffer);
    }
#endif
}

}  // namespace BillyEngine