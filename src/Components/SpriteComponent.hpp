#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"
#include "../Rendering/DrawableTexture.hpp"
#include "../Wrappers/Texture.hpp"

namespace BillyEngine {
namespace Components {
struct Sprite {
    Sprite() = default;
    Sprite(Ref<Texture> texture, const Color& tint = Color::white)
        : m_Texture(texture), Tint(tint) {}
    Sprite(Ref<DrawableTexture> dt, const Color& tint = Color::white)
        : m_DrawableTexture(dt), Tint(tint) {
        m_Texture = m_DrawableTexture->GetTextureOrNull();
    }

   private:
    Ref<Texture> m_Texture = nullptr;
    Ref<DrawableTexture> m_DrawableTexture = nullptr;

   public:
    Color Tint = Color::white;
    Ref<Texture> GetTexture() {
        if (m_DrawableTexture != nullptr)
            m_Texture = m_DrawableTexture->GetTextureOrNull();

        return m_Texture;
    }
};

}  // namespace Components
}  // namespace BillyEngine