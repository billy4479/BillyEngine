#include <BillyEngine/Application.h>

#include <iostream>

#include "Application.hpp"

Application* CreateApplication() {
    return (Application*)new BillyEngine::Application();
}

void DestroyApplication(Application* app) {
    delete (BillyEngine::Application*)app;
}

void RunApplication(Application* app) {
    ((BillyEngine::Application*)app)->Run();
}

void QuitApplication(Application* app) {
    ((BillyEngine::Application*)app)->Quit();
}
