#include "Surface.hpp"

namespace BillyEngine {
Surface::Surface(glm::ivec2 size) {
    m_Surface = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, 32,
                                               Color::PixelFormat);
    BE_CHECK_SDL_ERROR_AND_DIE();
}
Surface::Surface(SDL_Surface* surface) : m_Surface(surface) {
    BE_ASSERT(surface != nullptr);
    BE_CHECK_SDL_ERROR_AND_DIE();
}
Surface::Surface(Surface&& other) {
    this->m_Surface = other.m_Surface;
    other.m_Surface = nullptr;
}
Surface& Surface::operator=(Surface&& other) {
    if (this != &other) {
        this->m_Surface = other.m_Surface;
        other.m_Surface = nullptr;
    }
    return *this;
}
Surface::~Surface() {
    SDL_FreeSurface(m_Surface);
    BE_CHECK_SDL_ERROR_AND_DIE();
}
}  // namespace BillyEngine