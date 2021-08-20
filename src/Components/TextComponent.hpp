#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct Text {
    std::string Content;
    TTF_Font* Font = nullptr;
    SDL_Texture* Texture = nullptr;
    Color fgColor;

    Text(const std::string& text, TTF_Font* font,
         const Color& color = Color::white)
        : Content(text), Font(font), fgColor(color) {}
    Text(const Text&) = delete;
    ~Text() { SDL_DestroyTexture(Texture); }

    void UpdateText(const std::string& text) {
        Content = text;
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }

    void UpdateColor(const Color& color) {
        fgColor = color;
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }

    Text(Text&& other) noexcept {
        this->Texture = other.Texture;
        other.Texture = nullptr;

        this->Font = other.Font;
        other.Font = nullptr;

        this->Content = std::move(other.Content);
        this->fgColor = other.fgColor;
    }
    Text& operator=(Text&& other) noexcept {
        if (this != &other) {
            this->Texture = other.Texture;
            other.Texture = nullptr;

            this->Font = other.Font;
            other.Font = nullptr;

            this->Content = std::move(other.Content);
            this->fgColor = other.fgColor;
        }
        return *this;
    }
};

}  // namespace Components
}  // namespace BillyEngine