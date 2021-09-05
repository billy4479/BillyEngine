#include "DrawableTexture.hpp"

namespace BillyEngine {
#ifdef DEBUG
    #define CHECK_ERR()                                    \
        if (lockR != 0) dbg_print("%s\n", SDL_GetError()); \
        BE_ASSERT(lockR == 0);
#else
    #define CHECK_ERR() 0
#endif

#define LOCK_AND_GET_PIXELS()                                \
    auto lockR = SDL_LockSurface(m_Surface->AsSDLSurface()); \
    CHECK_ERR();                                             \
    u32* pixels = (u32*)m_Surface->AsSDLSurface()->pixels

#define UNLOCK() SDL_UnlockSurface(m_Surface->AsSDLSurface());

#define DO_WITH_PIXELS(...) \
    LOCK_AND_GET_PIXELS();  \
    {__VA_ARGS__};          \
    UNLOCK();

#define TO_PIXEL_COORDS(x, y) \
    y*(m_Surface->AsSDLSurface()->pitch / sizeof(u32)) + x

void DrawableTexture::PutPixel(glm::ivec2 position, const Color& c) {
    DO_WITH_PIXELS(pixels[TO_PIXEL_COORDS(position.x, position.y)] = c;)
}

void DrawableTexture::Clear(const Color& c) {
    SDL_FillRect(m_Surface->AsSDLSurface(), nullptr, c);
}

void DrawableTexture::Finalize() {
    m_Texture = CreateRef<Texture>(m_Surface, m_Renderer);
    m_HasTexture = true;
}

DrawableTexture::DrawableTexture(Ref<Renderer> renderer, glm::ivec2 size)
    : m_Renderer(renderer), m_Size(size) {
    m_Surface = CreateRef<Surface>(size);
    BE_ASSERT(m_Surface != nullptr);
}

}  // namespace BillyEngine