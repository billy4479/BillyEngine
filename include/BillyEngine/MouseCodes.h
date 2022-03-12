#pragma once

#include "EnumerateMouseButtons.h"

#define o(k, n) Button##k = n,
enum MouseButtons { ENUMERATE_MOUSE_BUTTONS(o) };
#undef o

#undef ENUMERATE_MOUSE_BUTTONS