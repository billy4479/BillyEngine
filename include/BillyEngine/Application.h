#pragma once

#include "Utils.h"

BE_HEADER_START

struct Application;

BE_PUBLIC Application* CreateApplication();
BE_PUBLIC void DestroyApplication(Application*);

BE_PUBLIC void RunApplication(Application*);

BE_HEADER_END