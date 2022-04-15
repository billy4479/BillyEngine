#include "Renderer.hpp"

#include <glad/gl.h>

#include "Assets/AssetManager.hpp"
#include "Core/Color.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/ShaderProgram.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/VertexBuffer.hpp"

namespace BillyEngine {

static Ref<ShaderProgram> shaderProgram;

static f32 vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                         0.0f,  0.0f,  0.5f, 0.0f};
static Ref<VertexBuffer> vertexBuffer;
static Ref<VertexArray> vertexArray;

Renderer::Renderer(AssetManager& am) {
    // TODO: These are the base shaders, maybe inline them?
    auto vertex =
        am.Load<Shader>("vertex.glsl", "vert", Shader::ShaderType::Vertex);
    auto fragment =
        am.Load<Shader>("fragment.glsl", "frag", Shader::ShaderType::Fragment);

    shaderProgram = ShaderProgram::Create(vertex, fragment);

    am.Unload("vert");
    am.Unload("frag");

    vertexArray = VertexArray::Create();
    vertexArray->Bind();

    vertexBuffer = VertexBuffer::CreateStatic(
        vertices, sizeof(vertices), BufferType({ShaderDataType::Float3}));

    vertexArray->AddVertexBuffer(vertexBuffer);
}

Renderer::~Renderer() {}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->Use();
    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::SetClearColor(const Color& c) {
    auto data = c.Data();
    glClearColor(data.r, data.g, data.b, data.a);
}

}  // namespace BillyEngine