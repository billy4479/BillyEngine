#include "Texture.hpp"

#include "../Rendering/Renderer.hpp"
#include "Surface.hpp"

namespace BillyEngine {

Texture::Texture(Ref<Surface> surface, Renderer* renderer)
    : m_Renderer(renderer) {
    m_Texture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(),
                                             surface->AsSDLSurface());
    BE_CHECK_SDL_ERROR_AND_DIE();

    m_Renderer->RegisterDestructionCallback(this, [this]() {
        m_Texture = nullptr;
        m_ValidRenderer = false;
    });
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
    if (m_ValidRenderer) {
        m_Renderer->UnregisterDestructionCallback(this);
        SDL_DestroyTexture(m_Texture);
        BE_CHECK_SDL_ERROR();
    }
}

}  // namespace BillyEngine