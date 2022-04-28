#pragma once

#include <vector>

#include "Rendering/ShaderDataType.hpp"

namespace BillyEngine {

struct BufferElement {
    BufferElement(ShaderDataType::TypeEnum, bool normalized = false);

    ShaderDataType Type;
    bool Normalized{false};
    u32 Size{0};
    size_t Offset{0};
    u32 ComponentCount{0};
};

class BufferType {
   public:
    BufferType(std::initializer_list<BufferElement>);

    u32 GetStride() const;
    size_t Length() const;
    const BufferElement& At(size_t) const;

   private:
    u32 m_Stride{0};
    std::vector<BufferElement> m_Elements;
};

}  // namespace BillyEngine