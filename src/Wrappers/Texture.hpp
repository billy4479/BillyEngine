#pragma once

#include "../Core/Common.hpp"
#include "../Rendering/Renderer.hpp"
#include "Surface.hpp"

namespace BillyEngine {

struct Texture {
    Texture(Ref<Surface> surface, Ref<Renderer> renderer) {
        m_Texture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(),
                                                 surface->AsSDLSurface());
    }
    explicit Texture(SDL_Texture* texture) : m_Texture(texture) {}

    BE_NON_COPY_CONSTRUTIBLE(Texture)
    Texture(Texture&& other) {
        this->m_Texture = other.m_Texture;
        other.m_Texture = nullptr;
    }
    Texture& operator=(Texture&& other) {
        if (this != &other) {
            this->m_Texture = other.m_Texture;
            other.m_Texture = nullptr;
        }
        return *this;
    }

    inline SDL_Texture* AsSDLTexture() { return m_Texture; }

    ~Texture() { SDL_DestroyTexture(m_Texture); }

   private:
    SDL_Texture* m_Texture = nullptr;
};

}  // namespace BillyEngine