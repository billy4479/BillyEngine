#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

class IndexBuffer {
   public:
    static Ref<IndexBuffer> CreateStatic(const void* data, u32 size);
    static Ref<IndexBuffer> CreateDynamic(u32 size);

    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    u32 GetSize() const;
    u32 GetID() const;

    void SetData(const void* data, u32 size);

   private:
    u32 m_IndexBuffer{};

    u32 m_Size{};

    IndexBuffer(const void* data, u32 size);
};

}  // namespace BillyEngine