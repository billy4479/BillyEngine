#pragma once

#include <unordered_map>

#include "Core/Types.hpp"
#include "Rendering/Uniform.hpp"

namespace BillyEngine {

class Shader;

class ShaderProgram {
   public:
    static Ref<ShaderProgram> Create(const Ref<Shader> vertexShader,
                                     const Ref<Shader> fragmentShader);
    ~ShaderProgram();

    u32 GetID() const;
    void Use() const;

    template <typename T>
    Uniform<T> GetUniform(std::string_view name) {
        return {m_Program, GetUniformAndCheck(name)};
    }

   private:
    ShaderProgram(const Ref<Shader> vertexShader,
                  const Ref<Shader> fragmentShader);

    i32 GetUniformFromShader(std::string_view) const;
    i32 GetUniformAndCheck(std::string_view);
    std::unordered_map<std::string_view, i32> m_UniformCache;

    u32 m_Program{0};
};

}  // namespace BillyEngine