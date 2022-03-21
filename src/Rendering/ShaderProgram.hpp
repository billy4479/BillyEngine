#pragma once

#include <utility>

#include "Core/Types.hpp"

namespace BillyEngine {

class Shader;

class ShaderProgram {
   public:
    static Ref<ShaderProgram> Create(Ref<Shader> vertexShader,
                                     Ref<Shader> fragmentShader);
    ~ShaderProgram();

    u32 GetID();

   private:
    ShaderProgram(Ref<Shader> vertexShader, Ref<Shader> fragmentShader);
    u32 m_Program{0};
};

}  // namespace BillyEngine