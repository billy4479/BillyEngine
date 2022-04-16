#include <BillyEngine++/BillyEngine.hpp>
// #include <BillyEngine/BillyEngine.h>
// #include <BillyEngine/Renderer.h>

int main() {
    // Application* app = TheApplication();
    // auto renderer = ApplicationGetRenderer(app);
    // RendererSetWireframeView(renderer, true);
    // RendererSetClearColor(renderer, ColorFromRGBA(0xff, 0xff, 0xff));

    // RunApplication(app);

    auto& app = BillyEngine::Application::The();
    // app.GetRenderer().SetWireframeView(true);
    app.Run();
}