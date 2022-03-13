#pragma once

namespace BillyEngine {

class AssetManager;

class Renderer {
   public:
    Renderer(AssetManager&);
    ~Renderer();

    void Render();

   private:
};

}  // namespace BillyEngine