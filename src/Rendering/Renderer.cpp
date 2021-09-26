#include "Renderer.hpp"

#include "../Wrappers/Font.hpp"
#include "../Wrappers/Texture.hpp"
#include "DrawableTexture.hpp"

namespace BillyEngine {

Renderer::Renderer(SDL_Window* window)
    : m_Renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) {
    BE_PROFILE_FUNCTION();

    BE_CHECK_SDL_ERROR_AND_DIE();
}

Renderer::~Renderer() {
    if (m_Renderer == nullptr) return;
    SDL_DestroyRenderer(m_Renderer);
    for (auto callback : m_DestructionCallbacks) {
        callback.second();
    }
    BE_CHECK_SDL_ERROR();
}

void Renderer::Clear() {
    BE_ASSERT(m_Renderer != nullptr);
    SDL_RenderClear(m_Renderer);
    BE_CHECK_SDL_ERROR_AND_DIE();
}

Ref<Texture> Renderer::RenderTextToTexture(
    const std::string& text, Ref<Font> font,
    const Color& fgColor /* TODO: config? */) {
    BE_ASSERT(m_Renderer != nullptr);

    auto tmpSurf = CreateRef<Surface>(
        TTF_RenderText_Blended(font->AsSDLFont(), text.c_str(), fgColor));
    auto texture = CreateRef<Texture>(tmpSurf, this);
    return texture;
}

void Renderer::DrawTexture(Ref<Texture> texture,
                           Components::Transform& transform, Color tint) {
    m_TextureBatch.push_back({texture, transform, tint});
}

void Renderer::DrawTextureInternal(TextureData& textureData) {
    auto [texture, t, tint] = textureData;

    BE_ASSERT(m_Renderer != nullptr);
    BE_ASSERT(texture != nullptr);

    i32 w, h;
    SDL_QueryTexture(texture->AsSDLTexture(), nullptr, nullptr, &w, &h);
    BE_CHECK_SDL_ERROR_AND_DIE();

    SDL_Rect sRect{0, 0, w, h};
    SDL_Rect dRect{t.Position.x, t.Position.y,
                   static_cast<i32>(abs(t.Scale.x) * (f32)w),
                   static_cast<i32>(abs(t.Scale.y) * (f32)h)};

    auto anchorPoint = CenterPointToCoords(t.Anchor, dRect);
    auto rotationCenterPoint = CenterPointToCoords(t.RotationCenter, dRect);

    dRect.x -= anchorPoint.x;
    dRect.y -= anchorPoint.y;

    i32 flip = SDL_FLIP_NONE;
    if (t.Scale.x < 0) flip |= SDL_FLIP_HORIZONTAL;
    if (t.Scale.y < 0) flip |= SDL_FLIP_VERTICAL;

    SDL_Point rotationCenterPointSDL = {rotationCenterPoint.x,
                                        rotationCenterPoint.y};

    SDL_SetTextureColorMod(texture->AsSDLTexture(), tint.r, tint.g, tint.b);
    BE_CHECK_SDL_ERROR_AND_DIE();
    SDL_SetTextureAlphaMod(texture->AsSDLTexture(), tint.a);
    BE_CHECK_SDL_ERROR_AND_DIE();
    SDL_RenderCopyEx(m_Renderer, texture->AsSDLTexture(), &sRect, &dRect,
                     t.Rotation, &rotationCenterPointSDL,
                     (SDL_RendererFlip)flip);
    BE_CHECK_SDL_ERROR_AND_DIE();
}

void Renderer::RegisterDestructionCallback(Texture* texture,
                                           std::function<void()> callback) {
    m_DestructionCallbacks[texture] = callback;
}

void Renderer::UnregisterDestructionCallback(Texture* texture) {
    m_DestructionCallbacks.erase(texture);
}

DrawableTexture Renderer::CreateDrawableTexture(glm::ivec2 size) {
    BE_ASSERT(m_Renderer != nullptr);

    return DrawableTexture(this, size);
}

void Renderer::RenderToScreen() {
    BE_PROFILE_FUNCTION();

    BE_ASSERT(m_Renderer != nullptr);

    std::sort(m_TextureBatch.begin(), m_TextureBatch.end(),
              [](const TextureData& tdata1, const TextureData& tdata2) {
                  return tdata1.Transform.zIndex < tdata2.Transform.zIndex;
              });
    for (auto& textureData : m_TextureBatch) {
        DrawTextureInternal(textureData);
    }
    m_TextureBatch.clear();

    SDL_RenderPresent(m_Renderer);
    BE_CHECK_SDL_ERROR_AND_DIE();
}

}  // namespace BillyEngine