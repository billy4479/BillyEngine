#pragma once

#include "../Core/CenterPoint.hpp"
#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

class DrawableTexture;
struct Texture;
struct Font;
class Renderer : public std::enable_shared_from_this<Renderer> {
   public:
    Renderer(SDL_Window *);
    BE_NON_COPY_CONSTRUTIBLE(Renderer)
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

    DrawableTexture CreateDrawableTexture(glm::ivec2 size);
    Ref<Texture> RenderTextToTexture(const std::string &text, Ref<Font> font,
                                     const Color &fgColor /* TODO: config? */);
    void DrawTexture(Ref<Texture> texture, glm::ivec2 position, glm::vec2 scale,
                     f32 rotation, CenterPoint anchor,
                     CenterPoint rotationCenter, Color tint = Color::white);

   private:
    SDL_Renderer *m_Renderer = nullptr;
};

}  // namespace BillyEngine