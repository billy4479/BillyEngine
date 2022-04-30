#pragma once

#include "Utils.h"

BE_HEADER_START

struct Application;
struct Renderer;

BE_API Application* TheApplication();
BE_API Application* CreateOrResetApplication();

BE_API void RunApplication(Application*);
BE_API void QuitApplication(Application*);

BE_API Renderer* ApplicationGetRenderer(Application*);

BE_HEADER_END