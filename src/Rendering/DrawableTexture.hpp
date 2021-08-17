#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
class DrawableTexture {
   public:
    void PutPixel(glm::ivec2 position, const Color& c);
    void Clear(const Color& c);
    operator SDL_Texture*() { return m_Texture; }

   public:
    DrawableTexture(SDL_Renderer* renderer, glm::ivec2 size);
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
    glm::ivec2 m_Size;
    SDL_Texture* m_Texture = nullptr;
};
}  // namespace BillyEngine