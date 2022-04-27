#pragma once

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
    Uniform<T> GetUniform(std::string_view name) const {
        return {m_Program, GetUniformAndCheck(name)};
    }

   private:
    ShaderProgram(const Ref<Shader> vertexShader,
                  const Ref<Shader> fragmentShader);

    i32 GetUniformAndCheck(std::string_view) const;

    u32 m_Program{0};
};

}  // namespace BillyEngine