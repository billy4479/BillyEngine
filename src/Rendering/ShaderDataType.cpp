#include "ShaderDataType.hpp"

#include <glad/gl.h>

namespace BillyEngine {

size_t ShaderDataType::Size() const {
    switch (Type) {
        case None:
            return 0;
        case Float:
            return 4;
        case Float2:
            return 4 * 2;
        case Float3:
            return 4 * 3;
        case Float4:
            return 4 * 4;
        case Mat3:
            return 4 * 3 * 3;
        case Mat4:
            return 4 * 4 * 4;
        case Int:
            return 4;
        case Int2:
            return 4 * 2;
        case Int3:
            return 4 * 3;
        case Int4:
            return 4 * 4;
        case Bool:
            return 1;
    }

    return 0;
}

u32 ShaderDataType::Count() const {
    switch (Type) {
        case Float:
            return 1;
        case Float2:
            return 2;
        case Float3:
            return 3;
        case Float4:
            return 4;
        case Mat3:
            return 3;  // 3* float3
        case Mat4:
            return 4;  // 4* float4
        case Int:
            return 1;
        case Int2:
            return 2;
        case Int3:
            return 3;
        case Int4:
            return 4;
        case Bool:
            return 1;
        default:
            return 0;
    }
}

u32 ShaderDataType::GLType() const {
    switch (Type) {
        case Float:
        case Float2:
        case Float3:
        case Float4:
            return GL_FLOAT;
        case Mat3:
        case Mat4:
            return GL_FLOAT;
        case Int:
        case Int2:
        case Int3:
        case Int4:
            return GL_INT;
        case Bool:
            return GL_BOOL;
        default:
            VERIFY_NOT_REACHED();
    }
}
}  // namespace BillyEngine