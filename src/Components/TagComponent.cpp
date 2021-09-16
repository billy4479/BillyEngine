#include "TagComponent.hpp"

namespace BillyEngine {
namespace Components {

Tag::Tag(const std::string& tag) : Name(tag) {}

Tag::Tag(Tag&& other) noexcept { this->Name = std::move(other.Name); }

Tag& Tag::operator=(Tag&& other) noexcept {
    if (this != &other) {
        this->Name = std::move(other.Name);
    }
    return *this;
}
}  // namespace Components
}  // namespace BillyEngine