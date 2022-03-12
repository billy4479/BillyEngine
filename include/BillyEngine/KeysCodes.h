#pragma once

#include "EnumerateKeys.h"

#define o(k, n) Key##k = n,
enum Keys { ENUMERATE_KEYS(o) };
#undef o

#undef ENUMERATE_KEYS