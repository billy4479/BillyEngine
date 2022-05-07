#pragma once

#include "Core/Types.hpp"
#include "Enumerate/EnumerateShaderDataTypes.h"

namespace BillyEngine {

struct ShaderDataType {
    using TypeEnum = u8;
    ShaderDataType(TypeEnum t) : Type(t) {}

#define o(t) t,
    enum : TypeEnum { ENUMERATE_SHADER_DATA_TYPES(o) };
#undef o

    u8 Type{None};

    size_t Size() const;
    u32 Count() const;
    u32 GLType() const;
};

}  // namespace BillyEngine