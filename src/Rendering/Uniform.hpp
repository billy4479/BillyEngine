#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

template <typename T>
class Uniform {
   public:
    Uniform(u32 program, i32 location)
        : m_Program(program), m_Location(location) {}
    ~Uniform() = default;

    // T Get();
    void Set(const T&);

   private:
    u32 m_Program{};
    i32 m_Location{};
};

}  // namespace BillyEngine