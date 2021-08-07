#include "BackBuffer.hpp"

namespace Rendering {

void BackBuffer::Init(i32 width, i32 height, SDL_Renderer *renderer) {
    assert(m_BackBuffer == nullptr);

    m_Height = height;
    m_Width = width;
    m_Renderer = renderer;

    m_BackBuffer = new u32[m_Width * m_Height];
    m_Pitch = m_Width * sizeof(i32);
    m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_ARGB32,
                                  SDL_TEXTUREACCESS_STATIC, m_Width, m_Height);
}

BackBuffer::~BackBuffer() {
    assert(m_BackBuffer != nullptr);

    SDL_DestroyTexture(m_Texture);
    delete[] m_BackBuffer;
    m_BackBuffer = nullptr;
}

void BackBuffer::Clear(Color c) {
    assert(m_BackBuffer != nullptr);

    for (i32 y = 0; y < m_Height; y++)
        for (i32 x = 0; x < m_Width; x++) m_BackBuffer[y * m_Width + x] = c;
}

void BackBuffer::Swap() {
    assert(m_BackBuffer != nullptr);

    SDL_RenderClear(m_Renderer);
    SDL_UpdateTexture(m_Texture, nullptr, m_BackBuffer, m_Pitch);
    SDL_RenderCopy(m_Renderer, m_Texture, nullptr, nullptr);
    for (auto tex : m_Textures) {
        if (tex.first != nullptr) {
            SDL_RenderCopy(m_Renderer, tex.first, nullptr, tex.second);
        }
    }
    SDL_RenderPresent(m_Renderer);
}

u32 &BackBuffer::At(i32 x, i32 y) {
    assert(m_BackBuffer != nullptr);
    assert(x < m_Width);
    assert(y < m_Height);

    return m_BackBuffer[y * m_Width + x];
}

void BackBuffer::PutTexture(SDL_Texture *texture, SDL_Rect *position) {
    m_Textures.push_back({texture, position});
}

void BackBuffer::DeleteTexture(SDL_Texture *texture) {
    for (size_t i = 0; i < m_Textures.size(); i++) {
        if (m_Textures[i].first == texture)
            m_Textures.erase(m_Textures.begin() + i);
    }
}

}  // namespace Rendering