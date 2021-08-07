#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace Entity {

// struct Component {
//     virtual void OnCreate() {};
//     virtual void OnUpdate(std::chrono::milliseconds deltaTime) {};
// };

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

    TextComponent(const std::string& text, TTF_Font* font)
        : Text(text), Font(font) {}
    TextComponent(const TextComponent&) = default;
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
    const std::function<void(std::chrono::milliseconds)> OnUpdate =
        [](std::chrono::milliseconds) {};

    ScriptComponent(std::function<void()> onCreate,
                    std::function<void(std::chrono::milliseconds)> onUpdate)
        : OnCreate(onCreate), OnUpdate(onUpdate) {
        onCreate();
    }
};

}  // namespace Entity
