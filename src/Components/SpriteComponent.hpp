#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

class Texture;
class DrawableTexture;

namespace Components {
class Sprite {
   public:
    Sprite();
    Sprite(Ref<Texture> texture, const Color& tint = Color::white);
    Sprite(Ref<DrawableTexture> dt, const Color& tint = Color::white);

    Color Tint = Color::white;
    Ref<Texture> GetTexture();
    void SetTexture(Ref<Texture>);
    void SetTexture(Ref<DrawableTexture>);

   private:
    Ref<Texture> m_Texture = nullptr;
    Ref<DrawableTexture> m_DrawableTexture = nullptr;
};

}  // namespace Components
}  // namespace BillyEngine