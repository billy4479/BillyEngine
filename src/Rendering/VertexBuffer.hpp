#pragma once

#include "Core/Types.hpp"
#include "Rendering/BufferType.hpp"

namespace BillyEngine {

class VertexBuffer {
   public:
    static Ref<VertexBuffer> CreateStatic(const void* data, u32 size,
                                          const BufferType&);
    static Ref<VertexBuffer> CreateDynamic(u32 size, const BufferType&);
    ~VertexBuffer();

    u32 GetID() const;

    void Bind() const;
    void Unbind() const;

    void SetData(const void* data, u32 size);
    u32 GetSize() const;
    const BufferType& GetBufferType() const;

   private:
    VertexBuffer(const void* data, u32 size, const BufferType&);

    u32 m_VertexBuffer{0};
    u32 m_Size{0};
    BufferType m_Type;
};

}  // namespace BillyEngine