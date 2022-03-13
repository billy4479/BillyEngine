#include "Renderer.hpp"

#include <glad/glad.h>

#include "Assets/AssetManager.hpp"
#include "Core/Color.hpp"
#include "Rendering/Shader.hpp"

namespace BillyEngine {

static u32 shaderProgram;

static f32 vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                         0.0f,  0.0f,  0.5f, 0.0f};
static u32 VertexArrayObject;

static u32 CreateShaderProgram(Ref<Shader> vertex, Ref<Shader> fragment) {
    u32 program = glCreateProgram();
    glAttachShader(program, vertex->GetID());
    glAttachShader(program, fragment->GetID());
    glLinkProgram(program);

    i32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char buffer[512];
        glGetProgramInfoLog(program, sizeof(buffer), nullptr, buffer);
        Logger::Core()->error("Error while linking shaders: {}", buffer);
        return -1;
    }

    return program;
}

Renderer::Renderer(AssetManager& am) {
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    u32 VertexBufferObjects;
    glGenBuffers(1, &VertexBufferObjects);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjects);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto vertex =
        am.Load<Shader>("vertex.glsl", "vert", Shader::ShaderType::Vertex);
    auto fragment =
        am.Load<Shader>("fragment.glsl", "frag", Shader::ShaderType::Fragment);

    shaderProgram = CreateShaderProgram(vertex, fragment);
    // glUseProgram(shaderProgram);

    am.Unload("vert");
    am.Unload("frag");

    // https://docs.gl/gl4/glVertexAttribPointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
}

Renderer::~Renderer() {}

void Renderer::Render() {
    static Color c = ColorFromBytes(0xc3, 0xe8, 0x8d);

    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

}  // namespace BillyEngine