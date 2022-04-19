#include <BillyEngine/Application.h>

#include "Application.hpp"

Application* TheApplication() {
    return (Application*)&BillyEngine::Application::The();
}

void CreateOrResetApplication(Application*) {
    // delete (BillyEngine::Application*)app;
    BillyEngine::Application::CreateOrReset();
}

void RunApplication(Application* app) {
    ((BillyEngine::Application*)app)->Run();
}

void QuitApplication(Application* app) {
    ((BillyEngine::Application*)app)->Quit();
}

Renderer* ApplicationGetRenderer(Application* app) {
    return (Renderer*)&((BillyEngine::Application*)app)->GetRenderer();
}
