#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct Sprite {
    Sprite() = default;
    Sprite(const Sprite&) = delete;
    Sprite(SDL_Texture* texture, const Color& tint = Color::white)
        : Texture(texture), Tint(tint) {}

    Sprite(SDL_Texture** texture, const Color& tint = Color::white)
        : Texture(*texture), TexturePtr(texture), Tint(tint) {}

    Sprite(Sprite&& other) noexcept {
        this->Texture = other.Texture;
        other.Texture = nullptr;

        this->Tint = other.Tint;
    }
    Sprite& operator=(Sprite&& other) noexcept {
        if (this != &other) {
            this->Texture = other.Texture;
            other.Texture = nullptr;

            this->Tint = other.Tint;
        }
        return *this;
    }

    inline SDL_Texture* GetTexture() const {
        return TexturePtr ? *TexturePtr : Texture;
    }

   private:
    SDL_Texture* Texture = nullptr;

   public:
    SDL_Texture** TexturePtr = nullptr;
    Color Tint{0, 0, 0, 0};
};

}  // namespace Components
}  // namespace BillyEngine