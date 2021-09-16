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
        m_Texture = m_DrawableTexture->GetTextureOrNull();

    return m_Texture;
}
}  // namespace Components
}  // namespace BillyEngine