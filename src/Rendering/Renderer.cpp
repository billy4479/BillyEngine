#include "Renderer.hpp"

#include "../Wrappers/Font.hpp"
#include "../Wrappers/Texture.hpp"
#include "DrawableTexture.hpp"

namespace BillyEngine {

Renderer::Renderer(SDL_Window* window)
    : m_Renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) {}

Renderer::~Renderer() {
    if (m_Renderer == nullptr) return;
    SDL_DestroyRenderer(m_Renderer);
}

void Renderer::Clear() {
    BE_ASSERT(m_Renderer != nullptr);
    SDL_RenderClear(m_Renderer);
}

Ref<Texture> Renderer::RenderTextToTexture(
    const std::string& text, Ref<Font> font,
    const Color& fgColor /* TODO: config? */) {
    BE_ASSERT(m_Renderer != nullptr);

    auto tmpSurf = CreateRef<Surface>(
        TTF_RenderText_Blended(font->AsSDLFont(), text.c_str(), fgColor));
    auto texture = CreateRef<Texture>(tmpSurf, shared_from_this());
    return texture;
}

void Renderer::DrawTexture(Ref<Texture> texture, glm::ivec2 position,
                           glm::vec2 scale, f32 rotation, CenterPoint anchor,
                           CenterPoint rotationCenter) {
    BE_ASSERT(m_Renderer != nullptr);
    BE_ASSERT(texture != nullptr);

    i32 w, h;
    [[maybe_unused]] auto result =
        SDL_QueryTexture(texture->AsSDLTexture(), nullptr, nullptr, &w, &h);
#ifdef DEBUG
    if (result != 0) dbg_print("%s\n", SDL_GetError());
#endif
    BE_ASSERT(result == 0);

    SDL_Rect sRect{0, 0, w, h};
    SDL_Rect dRect{position.x, position.y, static_cast<i32>(abs(scale.x) * w),
                   static_cast<i32>(abs(scale.y) * h)};

    auto anchorPoint = CenterPointToCoords(anchor, dRect);
    auto rotationCenterPoint = CenterPointToCoords(rotationCenter, dRect);

    dRect.x -= anchorPoint.x;
    dRect.y -= anchorPoint.y;

    i32 flip = SDL_FLIP_NONE;
    if (scale.x < 0) flip |= SDL_FLIP_HORIZONTAL;
    if (scale.y < 0) flip |= SDL_FLIP_VERTICAL;

    SDL_Point rotationCenterPointSDL = {rotationCenterPoint.x,
                                        rotationCenterPoint.y};

    result = SDL_RenderCopyEx(m_Renderer, texture->AsSDLTexture(), &sRect,
                              &dRect, rotation, &rotationCenterPointSDL,
                              (SDL_RendererFlip)flip);

#ifdef DEBUG
    if (result != 0) dbg_print("%s\n", SDL_GetError());
#endif
    BE_ASSERT(result == 0);
}

DrawableTexture Renderer::CreateDrawableTexture(glm::ivec2 size) {
    BE_ASSERT(m_Renderer != nullptr);

    return DrawableTexture(shared_from_this(), size);
}

void Renderer::RenderToScreen() {
    BE_ASSERT(m_Renderer != nullptr);
    SDL_RenderPresent(m_Renderer);
}

}  // namespace BillyEngine