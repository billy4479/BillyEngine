#include "DrawableTexture.hpp"

namespace BillyEngine {

#ifdef DEBUG
    #define CHECK_ERR()                                    \
        if (lockR != 0) dbg_print("%s\n", SDL_GetError()); \
        assert(lockR == 0);
#else
    #define CHECK_ERR() 0
#endif

#define LOCK_AND_GET_PIXELS()                                                  \
    u32* pixels = nullptr;                                                     \
    i32 pitch = 0;                                                             \
    auto lockR = SDL_LockTexture(m_Texture, nullptr, (void**)&pixels, &pitch); \
    CHECK_ERR();

#define UNLOCK() SDL_UnlockTexture(m_Texture);

#define DO_WITH_PIXELS(...) \
    LOCK_AND_GET_PIXELS();  \
    {__VA_ARGS__};          \
    UNLOCK();

#define TO_PIXEL_COORDS(x, y) y*(pitch / sizeof(u32)) + x

void DrawableTexture::PutPixel(glm::ivec2 position, const Color& c) {
    DO_WITH_PIXELS(pixels[TO_PIXEL_COORDS(position.x, position.y)] = c;)
}

void DrawableTexture::Clear(const Color& c) {
    DO_WITH_PIXELS(
        for (i32 y = 0; y < m_Size.y; y++) for (i32 x = 0; x < m_Size.x; x++)
            pixels[y * m_Size.x + x] = c;)
}

DrawableTexture::DrawableTexture(SDL_Renderer* renderer, glm::ivec2 size)
    : m_Size(size) {
    m_Texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32,
                                  SDL_TEXTUREACCESS_STREAMING, size.x, size.y);
    assert(m_Texture != nullptr);
}

DrawableTexture::~DrawableTexture() {
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
}

}  // namespace BillyEngine