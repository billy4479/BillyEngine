#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {

class Surface;
class Renderer;

class Texture {
   public:
    Texture(Ref<Surface> surface, Ref<Renderer> renderer);
    explicit Texture(SDL_Texture* texture);

    BE_NON_COPY_CONSTRUTIBLE(Texture)
    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    inline SDL_Texture* AsSDLTexture() { return m_Texture; }

    ~Texture();

   private:
    SDL_Texture* m_Texture = nullptr;
};

}  // namespace BillyEngine