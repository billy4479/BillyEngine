#pragma once

#include "Utils.h"

BE_HEADER_START

struct Application;

BE_PUBLIC Application* TheApplication();
BE_PUBLIC void ResetApplication(Application*);

BE_PUBLIC void RunApplication(Application*);
BE_PUBLIC void QuitApplication(Application*);

BE_HEADER_END