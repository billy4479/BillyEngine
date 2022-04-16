#include <BillyEngine/Renderer.h>

#include "Rendering/Renderer.hpp"

void RendererSetClearColor(Renderer* renderer, const Color* color) {
    ((BillyEngine::Renderer*)renderer)
        ->SetClearColor(*(BillyEngine::Color*)color);
}

void RendererSetWireframeView(Renderer* renderer, bool enabled) {
    ((BillyEngine::Renderer*)renderer)->SetWireframeView(enabled);
}
