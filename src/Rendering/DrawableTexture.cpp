#include "DrawableTexture.hpp"

namespace BillyEngine {

#ifdef DEBUG
    #define CHECK_ERR()                                    \
        if (lockR != 0) dbg_print("%s\n", SDL_GetError()); \
        assert(lockR == 0);
#else
    #define CHECK_ERR() 0
#endif

#define LOCK_AND_GET_PIXELS()                \
    auto lockR = SDL_LockSurface(m_Surface); \
    CHECK_ERR();                             \
    u32* pixels = (u32*)m_Surface->pixels

#define UNLOCK() SDL_UnlockSurface(m_Surface);

#define DO_WITH_PIXELS(...) \
    LOCK_AND_GET_PIXELS();  \
    {__VA_ARGS__};          \
    UNLOCK();

#define TO_PIXEL_COORDS(x, y) y*(m_Surface->pitch / sizeof(u32)) + x

void DrawableTexture::PutPixel(glm::ivec2 position, const Color& c) {
    DO_WITH_PIXELS(pixels[TO_PIXEL_COORDS(position.x, position.y)] = c;)
}

void DrawableTexture::Clear(const Color& c) {
    SDL_FillRect(m_Surface, nullptr, c);
}

void DrawableTexture::Finalize() {
    if (m_Texture != nullptr) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
    m_IsFinalized = true;
}

DrawableTexture::DrawableTexture(SDL_Renderer* renderer, glm::ivec2 size)
    : m_Renderer(renderer), m_Size(size) {
    m_Surface = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, sizeof(Color),
                                               Color::PixelFormat);
    assert(m_Surface != nullptr);
}

DrawableTexture::~DrawableTexture() {
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
    SDL_FreeSurface(m_Surface);
    m_Surface = nullptr;
}

}  // namespace BillyEngine