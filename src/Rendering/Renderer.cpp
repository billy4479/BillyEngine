#include "Renderer.hpp"

namespace BillyEngine {

void Renderer::Init(SDL_Window* window) {
    assert(m_Renderer == nullptr);
    m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(m_Renderer != nullptr);
}

Renderer::~Renderer() {
    if (m_Renderer == nullptr) return;
    SDL_DestroyRenderer(m_Renderer);
}

void Renderer::Clear() {
    assert(m_Renderer != nullptr);
    SDL_RenderClear(m_Renderer);
}

SDL_Texture* Renderer::RenderTextToTexture(
    const std::string& text, TTF_Font* font,
    const Color& fgColor /* TODO: config? */) {
    assert(m_Renderer != nullptr);

    auto tmpSurf = TTF_RenderText_Blended(font, text.c_str(), fgColor);
    auto texture = SDL_CreateTextureFromSurface(m_Renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    return texture;
}

void Renderer::DrawTexture(SDL_Texture* texture, std::pair<i32, i32> position,
                           std::pair<f32, f32> scale, f32 rotation,
                           std::pair<i32, i32> center) {
    assert(m_Renderer != nullptr);

    i32 w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Rect sRect{0, 0, w, h};
    SDL_Rect dRect{position.first, position.second,
                   static_cast<i32>(abs(scale.first) * w),
                   static_cast<i32>(abs(scale.second) * h)};
    SDL_Point c{center.first, center.second};

    i32 flip = SDL_FLIP_NONE;
    if (scale.first < 0) flip |= SDL_FLIP_HORIZONTAL;
    if (scale.second < 0) flip |= SDL_FLIP_VERTICAL;

    auto result = SDL_RenderCopyEx(m_Renderer, texture, &sRect, &dRect,
                                   rotation, &c, (SDL_RendererFlip)flip);

#ifdef DEBUG
    if (result != 0) dbg_print("%s\n", SDL_GetError());
#endif
    assert(result == 0);
}

DrawableTexture Renderer::CreateDrawableTexture(i32 width, i32 height) {
    assert(m_Renderer != nullptr);

    return DrawableTexture(m_Renderer, width, height);
}

void Renderer::RenderToScreen() {
    assert(m_Renderer != nullptr);
    SDL_RenderPresent(m_Renderer);
}

}  // namespace BillyEngine