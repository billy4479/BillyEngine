#pragma once

#include <vector>

#include "Core/Types.hpp"

namespace BillyEngine {

class VertexBuffer;
class IndexBuffer;

class VertexArray {
   public:
    static Ref<VertexArray> Create();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(const Ref<VertexBuffer>);
    void SetIndexBuffer(const Ref<IndexBuffer>);

    u32 GetIndiciesNumber() const;

   private:
    VertexArray();

    u32 m_VertexArray{0};

    u32 m_VertexBufferIndex{0};
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
};

}  // namespace BillyEngine