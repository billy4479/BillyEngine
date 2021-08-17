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

void Renderer::DrawTexture(SDL_Texture* texture, glm::ivec2 position,
                           glm::vec2 scale, f32 rotation, CenterPoint center) {
    assert(m_Renderer != nullptr);

    i32 w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Rect sRect{0, 0, w, h};
    SDL_Rect dRect{position.x, position.y, static_cast<i32>(abs(scale.x) * w),
                   static_cast<i32>(abs(scale.y) * h)};

    SDL_Point c;
    switch (center) {
        case CenterPoint::TOP_LEFT:
            c = {0, 0};
            break;
        case CenterPoint::TOP_CENTER:
            c = {dRect.w / 2, 0};
            break;
        case CenterPoint::TOP_RIGHT:
            c = {dRect.w, 0};
            break;
        case CenterPoint::CENTER_LEFT:
            c = {0, dRect.h / 2};
            break;
        case CenterPoint::CENTER_CENTER:
            c = {dRect.w / 2, dRect.h / 2};
            break;
        case CenterPoint::CENTER_RIGHT:
            c = {dRect.w, dRect.h / 2};
            break;
        case CenterPoint::BOTTOM_LEFT:
            c = {0, dRect.h};
            break;
        case CenterPoint::BOTTOM_CENTER:
            c = {dRect.w / 2, dRect.h};
            break;
        case CenterPoint::BOTTOM_RIGHT:
            c = {dRect.w, dRect.h};
            break;
    }

    dRect.x -= c.x;
    dRect.y -= c.y;

    i32 flip = SDL_FLIP_NONE;
    if (scale.x < 0) flip |= SDL_FLIP_HORIZONTAL;
    if (scale.y < 0) flip |= SDL_FLIP_VERTICAL;

    auto result = SDL_RenderCopyEx(m_Renderer, texture, &sRect, &dRect,
                                   rotation, &c, (SDL_RendererFlip)flip);

#ifdef DEBUG
    if (result != 0) dbg_print("%s\n", SDL_GetError());
#endif
    assert(result == 0);
}

DrawableTexture Renderer::CreateDrawableTexture(glm::ivec2 size) {
    assert(m_Renderer != nullptr);

    return DrawableTexture(m_Renderer, size);
}

void Renderer::RenderToScreen() {
    assert(m_Renderer != nullptr);
    SDL_RenderPresent(m_Renderer);
}

}  // namespace BillyEngine