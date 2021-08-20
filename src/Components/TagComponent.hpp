#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct Tag {
    std::string Name;

    Tag() = default;
    Tag(const Tag&) = delete;
    Tag(const std::string& tag) : Name(tag) {}

    Tag(Tag&& other) noexcept { this->Name = std::move(other.Name); }
    Tag& operator=(Tag&& other) noexcept {
        if (this != &other) {
            this->Name = std::move(other.Name);
        }
        return *this;
    }
};
}  // namespace Components
}  // namespace BillyEngine