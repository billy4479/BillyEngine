#pragma once

#include "Aliases.hpp"

namespace BillyEngine {

class UUID {
   public:
    UUID();
    UUID(u64);
    operator u64() const;

    std::string ToString() const;

   private:
    u64 m_UUID;
};

}  // namespace BillyEngine