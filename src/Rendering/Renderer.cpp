#include "Renderer.hpp"

#include <glad/glad.h>

#include "Core/Color.hpp"

namespace BillyEngine {

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render() {
    static Color c = ColorFromBytes(0xc3, 0xe8, 0x8d);

    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace BillyEngine