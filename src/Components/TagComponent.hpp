#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
class Tag {
   public:
    std::string Name;

    Tag(const std::string& tag);

    Tag(Tag&& other) noexcept;
    Tag& operator=(Tag&& other) noexcept;
};
}  // namespace Components
}  // namespace BillyEngine