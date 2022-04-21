#pragma once

#include <glm/ext/vector_int2.hpp>

#include "Core/Color.hpp"

namespace BillyEngine {

class AssetManager;
class VertexArray;
class ShaderProgram;

class Renderer {
   public:
    Renderer(AssetManager&);
    ~Renderer();

    void Clear() const;
    void Draw(Ref<VertexArray>, Ref<ShaderProgram> = nullptr) const;

    void SetClearColor(const Color&) const;
    void SetWireframeView(bool) const;
    void SetViewportSize(glm::ivec2) const;
    void SetVSync(bool) const;

    Ref<ShaderProgram> GetDefaultShader() const;

   private:
    struct RenderData;
    Scope<RenderData> m_RenderData;

    void LoadDefaultShader(AssetManager&);
};

}  // namespace BillyEngine