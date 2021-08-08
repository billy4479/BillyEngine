#pragma once

#include <SDL_render.h>

#include "../Core/Common.hpp"
#include "BackBuffer.hpp"

namespace Rendering {

class Renderer {
   public:
    Renderer() = default;
    ~Renderer();

    SDL_Renderer *GetSDLRenderer() { return m_Renderer; }

    void Init(SDL_Window *, i32, i32);
    void DrawToScreen();

    void Clear(Color &);
    void PutPixel(i32, i32, Color &);
    SDL_Texture *RenderTextToTexture(const std::string &text, TTF_Font *font,
                                     const Color &fgColor /* TODO: config? */);
    void DrawTexture(SDL_Texture *, std::pair<f32, f32> position,
                     std::pair<f32, f32> scale, f32 rotation);

   private:
    SDL_Renderer *m_Renderer = nullptr;
    BackBuffer m_BackBuffer;
};

}  // namespace Rendering