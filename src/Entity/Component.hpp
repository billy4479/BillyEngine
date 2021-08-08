#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace Entity {

struct TagComponent {
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag) : Tag(tag) {}
};

struct SpriteComponent {
    SDL_Texture* Texture = nullptr;
    Color Tint{0, 0, 0, 0};

    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = default;
    SpriteComponent(SDL_Texture* texture, const Color& tint = {0, 0, 0, 0})
        : Texture(texture), Tint(tint) {}
};

struct TextComponent {
    std::string Text;
    TTF_Font* Font = nullptr;
    SDL_Texture* Texture = nullptr;
    Color fgColor;

    TextComponent(const std::string& text, TTF_Font* font, const Color& color)
        : Text(text), Font(font), fgColor(color) {}
    TextComponent(const TextComponent&) = default;
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
};

struct TransformComponent {
    std::pair<f32, f32> Position = {0, 0};
    std::pair<f32, f32> Scale = {1, 1};
    f32 Rotation = 0;

    TransformComponent(std::pair<f32, f32> position, std::pair<f32, f32> scale,
                       f32 rotation)
        : Position(position), Scale(scale), Rotation(rotation) {}
    TransformComponent() = default;
};

struct ScriptComponent {
    const std::function<void()> OnCreate = []() {};
    const std::function<void(f32)> OnUpdate = [](f32) {};

    ScriptComponent(std::function<void()> onCreate,
                    std::function<void(f32)> onUpdate)
        : OnCreate(onCreate), OnUpdate(onUpdate) {
        onCreate();
    }
};

}  // namespace Entity
