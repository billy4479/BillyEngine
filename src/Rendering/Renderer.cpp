#include "Renderer.hpp"

namespace Rendering {

void Renderer::Init(SDL_Window *window, i32 w, i32 h) {
    assert(m_Renderer == nullptr);
    m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(m_Renderer != nullptr);

    m_BackBuffer.Init(w, h, GetSDLRenderer());
}

Renderer::~Renderer() { SDL_DestroyRenderer(GetSDLRenderer()); }

void Renderer::PutPixel(i32 x, i32 y, Color c) {
    assert(m_Renderer != nullptr);
    m_BackBuffer.At(x, y) = c;
    return;
}

void Renderer::Clear(Color c) { m_BackBuffer.Clear(c); }

void Renderer::Draw() { m_BackBuffer.Swap(); }

}  // namespace Rendering