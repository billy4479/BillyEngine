#include "VertexArray.hpp"

#include <glad/gl.h>

#include "Core/Logger.hpp"
#include "Rendering/BufferType.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "Rendering/VertexBuffer.hpp"

namespace BillyEngine {

Ref<VertexArray> VertexArray::Create() {
    return Ref<VertexArray>(new VertexArray());
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_VertexArray);
    BE_GL_LOG("glGenVertexArrays(1, {})", m_VertexArray);
}

VertexArray::~VertexArray() {
    BE_GL_LOG("glDeleteVertexArrays(1, {})", m_VertexArray);
    glDeleteVertexArrays(1, &m_VertexArray);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_VertexArray);
    BE_GL_LOG("glBindVertexArray({})", m_VertexArray);
}

void VertexArray::Unbind() const {
    BE_GL_LOG("glBindVertexArray(0)");
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer) {
    // TODO: For now we assume that there's just one vertex buffer made out of
    //        floats, but that is going to change soon

    Bind();
    vertexBuffer->Bind();

    const auto& bufType = vertexBuffer->GetBufferType();

    for (size_t i = 0; i < bufType.Length(); i++) {
        const auto& element = bufType.At(i);
        const auto& type = element.Type;

        switch (type.Type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: {
                BE_GL_LOG("glVertexAttribPointer({}, {}, GL_FLOAT, {}, {}, {})",
                          m_VertexBufferIndex, element.ComponentCount,
                          element.Normalized, bufType.GetStride(),
                          element.Offset);
                glVertexAttribPointer(m_VertexBufferIndex,
                                      element.ComponentCount, type.GLType(),
                                      element.Normalized, bufType.GetStride(),
                                      (const void*)element.Offset);

                BE_GL_LOG("glEnableVertexAttribArray({})", m_VertexBufferIndex);
                glEnableVertexAttribArray(m_VertexBufferIndex);

                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            case ShaderDataType::Bool: {
                BE_GL_LOG("glEnableVertexAttribArray({})", m_VertexBufferIndex);
                glEnableVertexAttribArray(m_VertexBufferIndex);

                BE_GL_LOG("glVertexAttribIPointer({}, {}, {}, {}, {}, {})",
                          m_VertexBufferIndex, element.ComponentCount,
                          type.Type, element.Normalized, bufType.GetStride(),
                          element.Offset);
                glVertexAttribIPointer(
                    m_VertexBufferIndex, element.ComponentCount, type.GLType(),
                    bufType.GetStride(), (const void*)element.Offset);
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4: {
                auto count = element.ComponentCount;
                for (u8 i = 0; i < count; i++) {
                    BE_GL_LOG("glEnableVertexAttribArray({})",
                              m_VertexBufferIndex);
                    glEnableVertexAttribArray(m_VertexBufferIndex);

                    BE_GL_LOG("glVertexAttribPointer({}, {}, {}, {}, {}, {})",
                              m_VertexBufferIndex, count, type.Type,
                              element.Normalized, bufType.GetStride(),
                              element.Offset + count * i * sizeof(f32));
                    glVertexAttribPointer(
                        m_VertexBufferIndex, count, type.GLType(),
                        element.Normalized, bufType.GetStride(),
                        (const void*)(element.Offset +
                                      count * i * sizeof(f32)));
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }

                break;
            }
            default:
                VERIFY_NOT_REACHED();
        }
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> indexBuffer) {
    Bind();
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}

u32 VertexArray::GetIndiciesNumber() const { return m_IndexBuffer->GetSize(); }

}  // namespace BillyEngine