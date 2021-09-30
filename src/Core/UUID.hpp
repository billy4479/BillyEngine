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

namespace std {

template <typename T>
struct hash;

template <>
struct hash<BillyEngine::UUID> {
    std::size_t operator()(const BillyEngine::UUID& uuid) const {
        return (uint64_t)uuid;
    }
};

}  // namespace std