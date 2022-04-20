#include "Renderer.hpp"

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <Generated.hpp>

#include "Assets/AssetManager.hpp"
#include "Core/Color.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/ShaderProgram.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/VertexBuffer.hpp"

namespace BillyEngine {

struct Renderer::RenderData {
    // static constexpr f32 vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
    //                                    0.0f,  0.0f,  0.5f, 0.0f};

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

    Ref<ShaderProgram> shaderProgram;
    Ref<VertexArray> vertexArray;
    Scope<Uniform<f32>> xOffsetUniform;
    f32 offset = -0.5;
};

#if BE_GL_LOG

static void GLDebugCallback(u32 source, u32 type, u32 id, u32 severity,
                            i32 length, const char* message,
                            const void* userParam) {
    std::string_view _source;
    std::string_view _type;
    (void)userParam;
    (void)length;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            VERIFY_NOT_REACHED();
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            VERIFY_NOT_REACHED();
    }

    static constexpr std::string_view format =
        "Message {} from {} of type {}: {}";

    #define LOG_MESSAGE(severity) \
        Logger::GL()->severity(format, id, _source, _type, message)

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            LOG_MESSAGE(error);
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            LOG_MESSAGE(warn);
            break;

        case GL_DEBUG_SEVERITY_LOW:
            LOG_MESSAGE(info);
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            LOG_MESSAGE(trace);
            break;

        default:
            VERIFY_NOT_REACHED();
    }

    #undef LOG_MESSAGE
}

#endif

Renderer::Renderer(AssetManager& am)
    : m_RenderData(CreateScope<Renderer::RenderData>()) {
#if BE_GL_LOG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugCallback, nullptr);
#endif

    auto vertex = am.Load<Shader, true>(EngineResources::vertex, "vert",
                                        Shader::ShaderType::Vertex);
    auto fragment = am.Load<Shader, true>(EngineResources::fragment, "frag",
                                          Shader::ShaderType::Fragment);

    m_RenderData->shaderProgram = ShaderProgram::Create(vertex, fragment);
    m_RenderData->xOffsetUniform = CreateScope<Uniform<f32>>(
        m_RenderData->shaderProgram->GetUniform<f32>("xOffset"));

    am.Unload("vert");
    am.Unload("frag");

    m_RenderData->vertexArray = VertexArray::Create();
    m_RenderData->vertexArray->Bind();

    auto vertexBuffer = VertexBuffer::CreateStatic(
        m_RenderData->vertices, sizeof(m_RenderData->vertices),
        BufferType({
            ShaderDataType::Float3,  // Vertices
            ShaderDataType::Float3,  // Colors
        }));
    auto indexBuffer = IndexBuffer::CreateStatic(m_RenderData->indices,
                                                 sizeof(m_RenderData->indices));

    m_RenderData->vertexArray->SetIndexBuffer(indexBuffer);
    m_RenderData->vertexArray->AddVertexBuffer(vertexBuffer);

    SetClearColor(Color::FromRGBA32(0x333333ff));
}

Renderer::~Renderer() {}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_RenderData->shaderProgram->Use();
    m_RenderData->xOffsetUniform->Set(m_RenderData->offset);
    m_RenderData->offset += 0.001;

    // auto timeValue = glfwGetTime();
    // f32 greenValue = sin(timeValue) / 2.0f + 0.5f;
    // colorUniform->Set({0.0f, greenValue, 0.0f, 1.0f});

    m_RenderData->vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, m_RenderData->vertexArray->GetIndiciesNumber(),
                   GL_UNSIGNED_INT, 0);
}

void Renderer::SetClearColor(const Color& c) {
    auto data = c.Data();
    glClearColor(data.r, data.g, data.b, data.a);
}

void Renderer::SetWireframeView(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void Renderer::SetViewportSize(glm::ivec2 size) {
    glViewport(0, 0, size.x, size.y);
}

}  // namespace BillyEngine