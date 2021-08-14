#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
class DrawableTexture {
   public:
    void PutPixel(u32 x, u32 y, const Color& c);
    void Clear(const Color& c);
    operator SDL_Texture*() { return m_Texture; }

   public:
    DrawableTexture(SDL_Renderer* renderer, i32 width, i32 height);
    explicit DrawableTexture(SDL_Texture* texture) : m_Texture(texture) {}
    DrawableTexture(DrawableTexture& other) = delete;
    DrawableTexture(DrawableTexture&& other) {
        this->m_Texture = other.m_Texture;
        other.m_Texture = nullptr;
    }
    DrawableTexture& operator=(DrawableTexture&& other) {
        if (this != &other) {
            this->m_Texture = other.m_Texture;
            other.m_Texture = nullptr;
        }
        return *this;
    }
    ~DrawableTexture();

   private:
    i32 m_Width, m_Height;
    SDL_Texture* m_Texture = nullptr;
};
}  // namespace BillyEngine