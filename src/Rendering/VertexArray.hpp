#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

class VertexBuffer;

class VertexArray {
   public:
    static Ref<VertexArray> Create();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(const Ref<VertexBuffer>);

   private:
    VertexArray();

    u32 m_VertexArray{0};

    u32 m_VertexBufferIndex{0};
};

}  // namespace BillyEngine