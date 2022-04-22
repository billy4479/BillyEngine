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
    Ref<ShaderProgram> DefaultShader;
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

    LoadDefaultShader(am);

    SetClearColor(Color::FromRGBA32(0x333333ff));
}

Renderer::~Renderer() {}

void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Draw(Ref<VertexArray> vertexArray,
                    Ref<ShaderProgram> maybeShaderProg) const {
    Ref<ShaderProgram> shaderProg = maybeShaderProg == nullptr
                                        ? m_RenderData->DefaultShader
                                        : maybeShaderProg;
    shaderProg->Use();
    vertexArray->Bind();

    BE_LOG_GL_CALL("glDrawElements(GL_TRIANGLES, {}, GL_UNSIGNED_INT, 0)",
                   vertexArray->GetIndiciesCount());
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndiciesCount(),
                   GL_UNSIGNED_INT, 0);
}

void Renderer::SetClearColor(const Color& c) const {
    auto data = c.Data();
    glClearColor(data.r, data.g, data.b, data.a);
}

void Renderer::SetWireframeView(bool enabled) const {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void Renderer::SetViewportSize(glm::ivec2 size) const {
    glViewport(0, 0, size.x, size.y);
}

void Renderer::SetVSync(bool enabled) const { glfwSwapInterval(enabled); }

Ref<ShaderProgram> Renderer::GetDefaultShader() const {
    return m_RenderData->DefaultShader;
}

void Renderer::LoadDefaultShader(AssetManager& am) {
    auto vertex = am.LoadNoStore<Shader, true>(EngineResources::vertex,
                                               Shader::ShaderType::Vertex);
    auto fragment = am.LoadNoStore<Shader, true>(EngineResources::fragment,
                                                 Shader::ShaderType::Fragment);

    m_RenderData->DefaultShader = ShaderProgram::Create(vertex, fragment);
    m_RenderData->DefaultShader->Use();
}

}  // namespace BillyEngine