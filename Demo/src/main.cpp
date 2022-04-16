// #include <BillyEngine++/BillyEngine.hpp>
#include <BillyEngine/BillyEngine.h>
#include <BillyEngine/Renderer.h>

int main() {
    Application* app = TheApplication();
    auto renderer = ApplicationGetRenderer(app);
    RendererSetWireframeView(renderer, true);
    // RendererSetClearColor(renderer, ColorFromRGBA(0xff, 0xff, 0xff));

    RunApplication(app);

    // BillyEngine::Application::The().Run();
}