#pragma once

#include "../Core/CenterPoint.hpp"
#include "../Core/Common.hpp"
#include "DrawableTexture.hpp"

namespace BillyEngine {

class Renderer {
   public:
    Renderer() = default;
    Renderer(Renderer &other) = delete;
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

    SDL_Renderer *GetSDLRenderer() { return m_Renderer; }

    void Init(SDL_Window *);
    void Clear();
    void RenderToScreen();

    DrawableTexture CreateDrawableTexture(glm::ivec2 size);
    SDL_Texture *RenderTextToTexture(const std::string &text, TTF_Font *font,
                                     const Color &fgColor /* TODO: config? */);
    void DrawTexture(SDL_Texture *, glm::ivec2 position, glm::vec2 scale,
                     f32 rotation, CenterPoint center = CenterPoint::TOP_LEFT);

   private:
    SDL_Renderer *m_Renderer = nullptr;
};

}  // namespace BillyEngine