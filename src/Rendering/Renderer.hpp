#pragma once

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

   private:
};

}  // namespace BillyEngine