#include "Renderer.hpp"

namespace Rendering {

void Renderer::Init(SDL_Window* window, i32 w, i32 h) {
    assert(m_Renderer == nullptr);
    m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(m_Renderer != nullptr);

    m_BackBuffer.Init(w, h, GetSDLRenderer());
}

Renderer::~Renderer() { SDL_DestroyRenderer(GetSDLRenderer()); }

void Renderer::PutPixel(i32 x, i32 y, Color& c) {
    assert(m_Renderer != nullptr);
    m_BackBuffer.At(x, y) = c;
    return;
}

SDL_Texture* Renderer::RenderTextToTexture(
    const std::string& text, TTF_Font* font,
    const Color& fgColor /* TODO: config? */) {
    auto tmpSurf = TTF_RenderText_Blended(font, text.c_str(), fgColor);
    auto texture = SDL_CreateTextureFromSurface(m_Renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    return texture;
}

void Renderer::DrawTexture(SDL_Texture*, std::pair<f32, f32> position,
                           std::pair<f32, f32> scale, f32 rotation) {
    (void)position;
    (void)scale;
    (void)rotation;
}

void Renderer::Clear(Color& c) { m_BackBuffer.Clear(c); }

void Renderer::DrawToScreen() { m_BackBuffer.Swap(); }

}  // namespace Rendering