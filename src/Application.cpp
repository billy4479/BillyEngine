#include "Application.hpp"

#include <Generated.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Assets/AssetManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Types.hpp"
#include "Events/EventManager.hpp"
#include "Events/Input.hpp"
#include "Events/KeyboardEvent.hpp"
#include "Events/WindowEvent.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/ShaderProgram.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

Application* Application::s_Instance{nullptr};

Application::Application(const ApplicationProprieties& props)
    : m_AssetManager(CreateScope<AssetManager>()),
      m_Window(CreateScope<Window>(props.Title, props.Size)),
      m_Renderer(CreateScope<Renderer>(*m_AssetManager)),
      m_EventManager(CreateScope<EventManager>(*m_Window)),
      m_Input(CreateScope<Input>(*m_Window)) {
    m_Renderer->SetViewportSize(props.Size);

    m_EventManager->AddListener<WindowResizeEvent>(
        [](const WindowResizeEvent& e) {
            Application::The().GetRenderer().SetViewportSize(e.Data.Size);
            Logger::Core()->debug("Resize to {}:{}", e.Data.Size.x,
                                  e.Data.Size.x);
        });

    m_Renderer->SetVSync(props.VSync);
}

void Application::Run() {
    Logger::Core()->info("Started!");

    // m_Renderer->SetWireframeView(true);
    auto wireframe = CreateRef<bool>(false);

    m_EventManager->AddListener<KeyTypedEvent>(
        [wireframe](const KeyboardEvent& e) {
            if (e.Data.Keycode == Keys::Backslash) {
                *wireframe = !*wireframe;
                Application::The().GetRenderer().SetWireframeView(*wireframe);
            }
        });

    auto vertexArray = VertexArray::Create();

    {
        struct Vertex {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 TextureCoord;
        };

        static constexpr Vertex vertices[] = {
            // bottom left
            Vertex{
                .Position = {-0.5f, -0.5f, 0.0f},
                .Color = {1.0f, 0.0f, 0.0f, 1.0f},
                .TextureCoord = {0.0f, 0.0f},
            },

            // bottom right
            Vertex{
                .Position = {0.5f, -0.5f, 0.0f},
                .Color = {0.0f, 1.0f, 0.0f, 1.0f},
                .TextureCoord = {1.0f, 0.0},
            },

            // top left
            Vertex{
                .Position = {-0.5f, 0.5f, 0.0f},
                .Color = {0.0f, 0.0f, 1.0f, 1.0f},
                .TextureCoord = {0.0f, 1.0f},
            },

            // top right
            Vertex{
                .Position = {0.5f, 0.5f, 0.0f},
                .Color = {1.0f, 1.0f, 0.0f, 1.0f},
                .TextureCoord = {1.0f, 1.0f},
            },
        };

        static constexpr u32 indices[] = {
            // 0, 1, 2,  // single triangle

            0, 1, 2,  // first triangle
            2, 3, 1   // second triangle
        };

        auto vertexBuffer = VertexBuffer::CreateStatic(
            vertices, sizeof(vertices),
            {ShaderDataType::Float3, ShaderDataType::Float4,
             ShaderDataType::Float2});
        auto indexBuffer = IndexBuffer::CreateStatic(indices, sizeof(indices));
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
    }

    f32 offset = -0.5;
    f32 increment = 0.01;
    auto xOffsetUniform =
        m_Renderer->GetDefaultShader()->GetUniform<f32>("xOffset");
    xOffsetUniform.Set(offset);

    // auto texture = GetAssetManager().LoadNoStore<Texture, true>(
    //     EngineResources::icon.Data.data(), EngineResources::icon.Size,
    //     EngineResources::icon.Channels);
    auto texture = GetAssetManager().LoadNoStore<Texture>("stock.png");
    texture->Bind(0);

    auto textureUniform =
        m_Renderer->GetDefaultShader()->GetUniform<i32>("Texture");
    textureUniform.Set(0);

    while (!m_Window->ShouldClose()) {
        m_EventManager->HandleEvents();
        m_Renderer->Clear();
        m_Renderer->Draw(vertexArray);
        m_Window->SwapBuffers();

        if (!m_Input->IsKeyPressed(Keys::Space)) {
            offset += increment;
            xOffsetUniform.Set(offset);
            if (offset >= 0.5) increment = -0.01;
            if (offset <= -0.5) increment = +0.01;
        }

        if (m_Input->IsKeyPressed(Keys::Escape)) Quit();
    }

    Logger::Core()->info("Stopped.");
}

void Application::Quit() { m_Window->SetShouldClose(true); }

Application& Application::The() {
    // We just die here since the logger might be uninitialized yet
    assert(s_Instance);

    return *s_Instance;
}

Application& Application::CreateOrReset(const ApplicationProprieties& props) {
    Logger::CreateOrReset();
    if (s_Instance) delete s_Instance;

    s_Instance = new Application(props);
    return *s_Instance;
}

Application::~Application() { Logger::Core()->info("Cleaning up."); }

}  // namespace BillyEngine
