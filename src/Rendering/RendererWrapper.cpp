#include <BillyEngine/Renderer.h>

#include "Rendering/Renderer.hpp"

BE_API void RendererSetClearColor(Renderer* renderer, const Color* color) {
    ((BillyEngine::Renderer*)renderer)
        ->SetClearColor(*(BillyEngine::Color*)color);
}

BE_API void RendererSetWireframeView(Renderer* renderer, bool enabled) {
    ((BillyEngine::Renderer*)renderer)->SetWireframeView(enabled);
}
