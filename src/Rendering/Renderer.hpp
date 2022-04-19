#pragma once

#include <glm/ext/vector_int2.hpp>

#include "Core/Color.hpp"

namespace BillyEngine {

class AssetManager;

class Renderer {
   public:
    Renderer(AssetManager&);
    ~Renderer();

    void Render();

    void SetClearColor(const Color&);
    void SetWireframeView(bool);

    void SetViewportSize(glm::ivec2);

   private:
    struct RenderData;
    Scope<RenderData> m_RenderData;
};

}  // namespace BillyEngine