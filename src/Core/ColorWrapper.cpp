#include <BillyEngine/Color.h>

#include "Core/Color.hpp"

Color* ColorFromRGBA32F(float r, float g, float b, float a) {
    return (Color*)new BillyEngine::Color({r, g, b, a});
}

Color* ColorFromRGBA32(uint32_t color) {
    return (Color*)new BillyEngine::Color(
        BillyEngine::Color::FromRGBA32(color));
}

Color* ColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (Color*)new BillyEngine::Color(
        BillyEngine::Color::FromRGBA({r, g, b, a}));
}

void ColorToRGBA32F(Color* c, float* r, float* g, float* b, float* a) {
    const auto& data = ((BillyEngine::Color*)c)->Data();
    if (r != nullptr) *r = data.r;
    if (g != nullptr) *g = data.g;
    if (b != nullptr) *b = data.b;
    if (a != nullptr) *a = data.a;
}

void ColorToRGBA32(Color* c, uint32_t* out) {
    *out = ((BillyEngine::Color*)c)->ToRGBA32();
}

void ColorToRGBA(Color* c, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) {
    const auto& data = ((BillyEngine::Color*)c)->ToRGBA();
    if (r != nullptr) *r = data.r;
    if (g != nullptr) *g = data.g;
    if (b != nullptr) *b = data.b;
    if (a != nullptr) *a = data.a;
}
