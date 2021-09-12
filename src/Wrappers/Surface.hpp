#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

struct Surface {
    Surface(glm::ivec2 size) {
        m_Surface = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, 32,
                                                   Color::PixelFormat);
        BE_CHECK_SDL_ERROR_AND_DIE();
    }
    explicit Surface(SDL_Surface* surface) : m_Surface(surface) {
        BE_ASSERT(surface != nullptr);
        BE_CHECK_SDL_ERROR_AND_DIE();
    }

    BE_NON_COPY_CONSTRUTIBLE(Surface)
    Surface(Surface&& other) {
        this->m_Surface = other.m_Surface;
        other.m_Surface = nullptr;
    }
    Surface& operator=(Surface&& other) {
        if (this != &other) {
            this->m_Surface = other.m_Surface;
            other.m_Surface = nullptr;
        }
        return *this;
    }

    inline SDL_Surface* AsSDLSurface() { return m_Surface; }

    ~Surface() {
        SDL_FreeSurface(m_Surface);
        BE_CHECK_SDL_ERROR_AND_DIE();
    }

   private:
    SDL_Surface* m_Surface = nullptr;
};

}  // namespace BillyEngine