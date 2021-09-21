#include "Texture.hpp"

#include "../Rendering/Renderer.hpp"
#include "Surface.hpp"

namespace BillyEngine {

Texture::Texture(Ref<Surface> surface, Ref<Renderer> renderer) {
    m_Texture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(),
                                             surface->AsSDLSurface());
    BE_CHECK_SDL_ERROR_AND_DIE();
}

Texture::Texture(SDL_Texture* texture) : m_Texture(texture) {
    BE_CHECK_SDL_ERROR_AND_DIE();
}

Texture::Texture(Texture&& other) {
    this->m_Texture = other.m_Texture;
    other.m_Texture = nullptr;
}

Texture& Texture::operator=(Texture&& other) {
    if (this != &other) {
        this->m_Texture = other.m_Texture;
        other.m_Texture = nullptr;
    }
    return *this;
}

Texture::~Texture() {
    // FIXME: Some weird stuff is going on here...
    // The last texture which gets destroyed generates an error, but since
    // this is not critical and I don't really know where the issue is, I'll
    // just ignore this for now :)
    SDL_DestroyTexture(m_Texture);
    BE_CHECK_SDL_ERROR();
}

}  // namespace BillyEngine