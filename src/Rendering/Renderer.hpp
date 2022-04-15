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

   private:
};

}  // namespace BillyEngine