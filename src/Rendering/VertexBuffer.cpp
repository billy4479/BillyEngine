#include "VertexBuffer.hpp"

#include <glad/gl.h>

#include <sstream>

#include "Core/Logger.hpp"

namespace BillyEngine {

Ref<VertexBuffer> VertexBuffer::CreateStatic(const void* data, u32 size,
                                             const BufferType& type) {
    return Ref<VertexBuffer>(new VertexBuffer(data, size, false, type));
}

Ref<VertexBuffer> VertexBuffer::CreateDynamic(u32 size,
                                              const BufferType& type) {
    return Ref<VertexBuffer>(new VertexBuffer(nullptr, size, true, type));
}

VertexBuffer::VertexBuffer(const void* data, u32 size, bool dynamic,
                           const BufferType& type)
    : m_Size(size), m_Type(type) {
    BE_GL_LOG("GL: VertexBuffer({}, {}, {}, [stride]{})", data, size, dynamic,
              type.GetStride());

    glGenBuffers(1, &m_VertexBuffer);
    BE_GL_LOG("GL: glGenBuffers(1, {})", m_VertexBuffer);
    Bind();

#if BE_GL_DEBUG
    auto v = (f32*)data;
    std::stringstream ss;
    for (size_t i = 0; i < size / sizeof(f32); i++) {
        ss << v[i] << ",";
    }

    BE_GL_LOG("BufferData: [{}]", ss.str());
#endif

    BE_GL_LOG("GL: glBufferData(GL_ARRAY_BUFFER, {}, {}, {})", size, data,
              dynamic ? "GL_DYNAMIC_DRAW" : "GL_STATIC_DRAW");
    glBufferData(GL_ARRAY_BUFFER, size, data,
                 dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    BE_GL_LOG("GL: glDeleteBuffers(1, {})", m_VertexBuffer);
    glDeleteBuffers(1, &m_VertexBuffer);
}

u32 VertexBuffer::GetID() const { return m_VertexBuffer; }

void VertexBuffer::Bind() const {
    BE_GL_LOG("GL: glBindBuffer(GL_ARRAY_BUFFER, {})", m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
}

void VertexBuffer::Unbind() const {
    BE_GL_LOG("GL: glBindBuffer(GL_ARRAY_BUFFER, 0)", m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, u32 size) {
    Bind();

    // https://docs.gl/gl4/glBufferSubData
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    BE_GL_LOG("GL: glBufferSubData(GL_ARRAY_BUFFER, 0, {}, {})", size, data);
}

u32 VertexBuffer::GetSize() const { return m_Size; }

const BufferType& VertexBuffer::GetBufferType() const { return m_Type; }

}  // namespace BillyEngine