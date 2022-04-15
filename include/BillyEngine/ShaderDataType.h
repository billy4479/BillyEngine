#pragma once

#include "EnumerateShaderDataTypes.h"

#define o(t) ShaderType##t,
enum Keys { ENUMERATE_SHADER_DATA_TYPES(o) };
#undef o

#undef ENUMERATE_SHADER_DATA_TYPES