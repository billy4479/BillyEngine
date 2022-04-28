#include "Rendering/IndexBuffer.hpp"

#include <glad/gl.h>

#include "Core/Logger.hpp"

namespace BillyEngine {
Ref<IndexBuffer> IndexBuffer::CreateStatic(const void* data, u32 size) {
    return Ref<IndexBuffer>(new IndexBuffer(data, size));
}

Ref<IndexBuffer> IndexBuffer::CreateDynamic(u32 size) {
    return Ref<IndexBuffer>(new IndexBuffer(nullptr, size));
}

IndexBuffer::~IndexBuffer() {
    BE_LOG_GL_CALL("glDeleteBuffers(1, {})", m_IndexBuffer);
    glDeleteBuffers(1, &m_IndexBuffer);
}

void IndexBuffer::Bind() const {
    BE_LOG_GL_CALL("glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, {})", m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
}

void IndexBuffer::Unbind() const {
    BE_LOG_GL_CALL("glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u32 IndexBuffer::GetSize() const { return m_Size; }

u32 IndexBuffer::GetID() const { return m_IndexBuffer; }

void IndexBuffer::SetData(const void* data, u32 size) {
    Bind();

    BE_LOG_GL_CALL("glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, {}, {})", size,
                   data);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

IndexBuffer::IndexBuffer(const void* data, u32 size) : m_Size(size) {
    glGenBuffers(1, &m_IndexBuffer);
    BE_LOG_GL_CALL("glGenBuffers(1, {})", m_IndexBuffer);

    Bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data,
                 data == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    BE_LOG_GL_CALL("glBufferData(GL_ELEMENT_ARRAY_BUFFER, {}, {}, {})", size,
                   data,
                   data == nullptr ? "GL_DYNAMIC_DRAW" : "GL_STATIC_DRAW");
}
}  // namespace BillyEngine