#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct TextComponent {
    std::string Text;
    TTF_Font* Font = nullptr;
    SDL_Texture* Texture = nullptr;
    Color fgColor;

    TextComponent(const std::string& text, TTF_Font* font,
                  const Color& color = Color::white)
        : Text(text), Font(font), fgColor(color) {}
    TextComponent(const TextComponent&) = delete;
    ~TextComponent() { SDL_DestroyTexture(Texture); }

    void UpdateText(const std::string& text) {
        Text = text;
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }

    void UpdateColor(const Color& color) {
        fgColor = color;
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }

    TextComponent(TextComponent&& other) noexcept {
        this->Texture = other.Texture;
        other.Texture = nullptr;

        this->Font = other.Font;
        other.Font = nullptr;

        this->Text = std::move(other.Text);
        this->fgColor = other.fgColor;
    }
    TextComponent& operator=(TextComponent&& other) noexcept {
        if (this != &other) {
            this->Texture = other.Texture;
            other.Texture = nullptr;

            this->Font = other.Font;
            other.Font = nullptr;

            this->Text = std::move(other.Text);
            this->fgColor = other.fgColor;
        }
        return *this;
    }
};

}  // namespace Components
}  // namespace BillyEngine