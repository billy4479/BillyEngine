#pragma once

#include "../Core/Common.hpp"
#include "DrawableTexture.hpp"

namespace BillyEngine {

class Renderer {
   public:
    Renderer() = default;
    Renderer(Renderer &other) = delete;
    Renderer(Renderer &&other) {
        this->m_Renderer = other.m_Renderer;
        other.m_Renderer = nullptr;
    }
    Renderer &operator=(Renderer &&other) {
        if (this != &other) {
            this->m_Renderer = other.m_Renderer;
            other.m_Renderer = nullptr;
        }
        return *this;
    }
    ~Renderer();

    SDL_Renderer *GetSDLRenderer() { return m_Renderer; }

    void Init(SDL_Window *);
    void Clear();
    void RenderToScreen();

    DrawableTexture CreateDrawableTexture(i32 width, i32 height);
    SDL_Texture *RenderTextToTexture(const std::string &text, TTF_Font *font,
                                     const Color &fgColor /* TODO: config? */);
    void DrawTexture(SDL_Texture *, std::pair<i32, i32> position,
                     std::pair<i32, i32> scale, f32 rotation,
                     std::pair<i32, i32> center = {0, 0});

   private:
    SDL_Renderer *m_Renderer = nullptr;
};

}  // namespace BillyEngine