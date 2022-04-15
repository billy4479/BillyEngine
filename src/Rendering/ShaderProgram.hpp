#pragma once

#include <utility>

#include "Core/Types.hpp"

namespace BillyEngine {

class Shader;

class ShaderProgram {
   public:
    static Ref<ShaderProgram> Create(const Ref<Shader> vertexShader,
                                     const Ref<Shader> fragmentShader);
    ~ShaderProgram();

    u32 GetID() const;
    void Use() const;

   private:
    ShaderProgram(const Ref<Shader> vertexShader,
                  const Ref<Shader> fragmentShader);
    u32 m_Program{0};
};

}  // namespace BillyEngine