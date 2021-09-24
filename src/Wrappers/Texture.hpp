#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {

class Surface;
class Renderer;

class Texture {
   public:
    Texture(Ref<Surface> surface, Renderer* renderer);
    explicit Texture(SDL_Texture* texture);

    BE_NON_COPY_CONSTRUCTIBLE(Texture)
    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    inline SDL_Texture* AsSDLTexture() { return m_Texture; }

    ~Texture();

   private:
    SDL_Texture* m_Texture = nullptr;
    Renderer* m_Renderer = nullptr;
    bool m_ValidRenderer = true;
};

}  // namespace BillyEngine