#include "SpriteComponent.hpp"

#include "../Rendering/DrawableTexture.hpp"
#include "../Wrappers/Texture.hpp"

namespace BillyEngine {
namespace Components {
Sprite::Sprite() = default;

Sprite::Sprite(Ref<Texture> texture, const Color& tint)
    : Tint(tint), m_Texture(texture) {}
Sprite::Sprite(Ref<DrawableTexture> dt, const Color& tint)
    : Tint(tint), m_DrawableTexture(dt) {
    m_Texture = m_DrawableTexture->GetTextureOrNull();
}
Ref<Texture> Sprite::GetTexture() {
    if (m_DrawableTexture != nullptr)
        return m_DrawableTexture->GetTextureOrNull();

    return m_Texture;
}

void Sprite::SetTexture(Ref<Texture> texture) {
    m_Texture = texture;
    m_DrawableTexture = nullptr;
}

void Sprite::SetTexture(Ref<DrawableTexture> dt) {
    m_DrawableTexture = dt;
    m_Texture = nullptr;
}
}  // namespace Components
}  // namespace BillyEngine