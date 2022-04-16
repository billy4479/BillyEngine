#include "Renderer.hpp"

#include <glad/gl.h>

#include "Assets/AssetManager.hpp"
#include "Core/Color.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/ShaderProgram.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/VertexBuffer.hpp"

namespace BillyEngine {

static Ref<ShaderProgram> shaderProgram;

// static f32 vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
//                          0.0f,  0.0f,  0.5f, 0.0f};

static constexpr f32 vertices[] = {
    +0.5f, +0.5f, 0.0f,  // top right
    +0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f, +0.5f, 0.0f   // top left
};
static constexpr u32 indices[] = {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

// static Ref<VertexBuffer> vertexBuffer;
// static Ref<IndexBuffer> indexBuffer;
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

    auto vertexBuffer = VertexBuffer::CreateStatic(
        vertices, sizeof(vertices), BufferType({ShaderDataType::Float3}));
    auto indexBuffer = IndexBuffer::CreateStatic(indices, sizeof(indices));

    vertexArray->SetIndexBuffer(indexBuffer);
    vertexArray->AddVertexBuffer(vertexBuffer);
}

Renderer::~Renderer() {}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->Use();
    // vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::SetClearColor(const Color& c) {
    auto data = c.Data();
    glClearColor(data.r, data.g, data.b, data.a);
}

void Renderer::SetWireframeView(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

}  // namespace BillyEngine