#include "Renderer.hpp"

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Assets/AssetManager.hpp"
#include "Core/Color.hpp"
#include "EngineAssets/Wrapper.hpp"
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
    // positions        // colors
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
};
static constexpr u32 indices[] = {
    0, 1, 2,  // single triangle

    // 0, 1, 3,  // first triangle
    // 1, 2, 3   // second triangle
};

static Ref<VertexArray> vertexArray;
static Scope<Uniform<f32>> xOffsetUniform;
static f32 offset = -0.5;

Renderer::Renderer(AssetManager& am) {
    auto vertex = am.Load<Shader, true>(EngineAssets::vertex, "vert",
                                        Shader::ShaderType::Vertex);
    auto fragment = am.Load<Shader, true>(EngineAssets::fragment, "frag",
                                          Shader::ShaderType::Fragment);

    shaderProgram = ShaderProgram::Create(vertex, fragment);
    xOffsetUniform =
        CreateScope<Uniform<f32>>(shaderProgram->GetUniform<f32>("xOffset"));

    am.Unload("vert");
    am.Unload("frag");

    vertexArray = VertexArray::Create();
    vertexArray->Bind();

    auto vertexBuffer =
        VertexBuffer::CreateStatic(vertices, sizeof(vertices),
                                   BufferType({
                                       ShaderDataType::Float3,  // Vertices
                                       ShaderDataType::Float3,  // Colors
                                   }));
    auto indexBuffer = IndexBuffer::CreateStatic(indices, sizeof(indices));

    vertexArray->SetIndexBuffer(indexBuffer);
    vertexArray->AddVertexBuffer(vertexBuffer);

    SetClearColor(Color::FromRGBA32(0x333333ff));
}

Renderer::~Renderer() {}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->Use();
    xOffsetUniform->Set(offset);
    offset += 0.001;

    // auto timeValue = glfwGetTime();
    // f32 greenValue = sin(timeValue) / 2.0f + 0.5f;
    // colorUniform->Set({0.0f, greenValue, 0.0f, 1.0f});

    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndiciesNumber(),
                   GL_UNSIGNED_INT, 0);
}

void Renderer::SetClearColor(const Color& c) {
    auto data = c.Data();
    glClearColor(data.r, data.g, data.b, data.a);
}

void Renderer::SetWireframeView(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

}  // namespace BillyEngine