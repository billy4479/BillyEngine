#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {
namespace Components {
struct TagComponent {
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = delete;
    TagComponent(const std::string& tag) : Tag(tag) {}

    TagComponent(TagComponent&& other) noexcept {
        this->Tag = std::move(other.Tag);
    }
    TagComponent& operator=(TagComponent&& other) noexcept {
        if (this != &other) {
            this->Tag = std::move(other.Tag);
        }
        return *this;
    }
};
}  // namespace Components
}  // namespace BillyEngine