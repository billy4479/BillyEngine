#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct SpriteComponent {
    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent(SDL_Texture* texture, const Color& tint = Color::white)
        : Texture(texture), Tint(tint) {}

    SpriteComponent(SDL_Texture** texture, const Color& tint = Color::white)
        : Texture(*texture), TexturePtr(texture), Tint(tint) {}

    SpriteComponent(SpriteComponent&& other) noexcept {
        this->Texture = other.Texture;
        other.Texture = nullptr;

        this->Tint = other.Tint;
    }
    SpriteComponent& operator=(SpriteComponent&& other) noexcept {
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