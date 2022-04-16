#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

template <typename T>
class Uniform {
   public:
    Uniform(i32 location) : m_Location(location) {}
    ~Uniform() = default;

    // T Get();
    void Set(const T&);

   private:
    i32 m_Location{};
};

}  // namespace BillyEngine