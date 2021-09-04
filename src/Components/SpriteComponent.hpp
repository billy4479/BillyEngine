#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"
#include "../Wrappers/Texture.hpp"

namespace BillyEngine {
namespace Components {
struct Sprite {
    Sprite() = default;
    Sprite(Ref<Texture> texture, const Color& tint = Color::white)
        : m_Texture(texture), Tint(tint) {}

    Ref<Texture> m_Texture = nullptr;
    Color Tint{0, 0, 0, 0};
};

}  // namespace Components
}  // namespace BillyEngine