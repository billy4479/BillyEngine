#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
class Tag {
   public:
    std::string Name;

    Tag(const std::string& tag) : Name(tag) {}

    Tag(const Tag& other) = default;
    Tag& operator=(const Tag& other) = default;
    Tag(Tag&& other) noexcept = default;
    Tag& operator=(Tag&& other) noexcept = default;
};
}  // namespace Components
}  // namespace BillyEngine