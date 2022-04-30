#include <BillyEngine/Application.h>

#include "Application.hpp"

BE_API Application* TheApplication() {
    return (Application*)&BillyEngine::Application::The();
}

BE_API void CreateOrResetApplication(Application*) {
    // delete (BillyEngine::Application*)app;
    BillyEngine::Application::CreateOrReset();
}

BE_API void RunApplication(Application* app) {
    ((BillyEngine::Application*)app)->Run();
}

BE_API void QuitApplication(Application* app) {
    ((BillyEngine::Application*)app)->Quit();
}

BE_API Renderer* ApplicationGetRenderer(Application* app) {
    return (Renderer*)&((BillyEngine::Application*)app)->GetRenderer();
}
