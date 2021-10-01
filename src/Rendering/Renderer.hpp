#pragma once

#include "../Components/TransformComponent.hpp"
#include "../Core/CenterPoint.hpp"
#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

namespace Components {
class Transform;
}

class DrawableTexture;
class Texture;
class Font;
class Renderer {
   public:
    Renderer(SDL_Window *);
    BE_NON_COPY_CONSTRUCTIBLE(Renderer)
    Renderer(Renderer &&other) {
        this->m_Renderer = other.m_Renderer;
        other.m_Renderer = nullptr;
    }
    Renderer &operator=(Renderer &&other) {
        if (this != &other) {
            this->m_Renderer = other.m_Renderer;
            other.m_Renderer = nullptr;
        }
        return *this;
    }
    ~Renderer();

    inline SDL_Renderer *GetSDLRenderer() { return m_Renderer; }

    void Clear();
    void RenderToScreen();

    Ref<Texture> RenderTextToTexture(const std::string &text, Ref<Font> font,
                                     const Color &fgColor /* TODO: config? */);

    void DrawTexture(Ref<Texture> texture, Components::Transform &,
                     Color tint = Color::white);

    void RegisterDestructionCallback(Texture *, std::function<void()>);
    void UnregisterDestructionCallback(Texture *);

   private:
    struct TextureData {
        Ref<Texture> Data;
        Components::Transform Transform;
        Color Tint;

        TextureData(Ref<Texture> data, const Components::Transform &transform,
                    Color tint)
            : Data(data), Transform(transform), Tint(tint) {}
        TextureData(const TextureData &) = default;
        TextureData(TextureData &&) = default;
        TextureData &operator=(const TextureData &) = default;
        TextureData &operator=(TextureData &&) = default;
        ~TextureData() = default;

        void swap(TextureData &other) {
            TextureData tmp = other;
            other.Data = Data;
            other.Tint = Tint;
            other.Transform = Transform;

            Data = tmp.Data;
            Tint = tmp.Tint;
            Transform = tmp.Transform;
        }
    };

    void DrawTextureInternal(TextureData &);
    std::vector<TextureData> m_TextureBatch;

    std::map<Texture *, std::function<void()>> m_DestructionCallbacks;
    SDL_Renderer *m_Renderer = nullptr;
};

}  // namespace BillyEngine