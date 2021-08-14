#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct SpriteComponent {
    SDL_Texture* Texture = nullptr;
    Color Tint{0, 0, 0, 0};

    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent(SDL_Texture* texture, const Color& tint = {0, 0, 0, 0})
        : Texture(texture), Tint(tint) {}

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
};

}  // namespace Components
}  // namespace BillyEngine