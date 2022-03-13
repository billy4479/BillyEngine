#include <BillyEngine/Application.h>

#include <iostream>

#include "Application.hpp"

Application* TheApplication() {
    return (Application*)&BillyEngine::Application::The();
}

void ResetApplication(Application*) {
    // delete (BillyEngine::Application*)app;
    BillyEngine::Application::Reset();
}

void RunApplication(Application* app) {
    ((BillyEngine::Application*)app)->Run();
}

void QuitApplication(Application* app) {
    ((BillyEngine::Application*)app)->Quit();
}
