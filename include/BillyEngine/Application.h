#pragma once

#include "Utils.h"

BE_HEADER_START

struct Application;
struct Renderer;

BE_PUBLIC Application* TheApplication();
BE_PUBLIC Application* CreateOrResetApplication();

BE_PUBLIC void RunApplication(Application*);
BE_PUBLIC void QuitApplication(Application*);

BE_PUBLIC Renderer* ApplicationGetRenderer(Application*);

BE_HEADER_END