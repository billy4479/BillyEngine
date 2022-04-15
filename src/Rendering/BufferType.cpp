#include "BufferType.hpp"

#include <glad/gl.h>

namespace BillyEngine {

BufferElement::BufferElement(ShaderDataType::TypeEnum type, bool normalized)
    : Type(type),
      Normalized(normalized),
      Size(Type.Size()),
      ComponentCount(Type.Count()) {}

BufferType::BufferType(std::initializer_list<BufferElement> elements)
    : m_Elements(elements) {
    u32 offset = 0;
    m_Stride = 0;
    for (auto& element : m_Elements) {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

u32 BufferType::GetStride() const { return m_Stride; }

size_t BufferType::Length() const { return m_Elements.size(); }

const BufferElement& BufferType::At(size_t i) const { return m_Elements.at(i); }

}  // namespace BillyEngine