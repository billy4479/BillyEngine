#pragma once

#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <string_view>

#include "Core/Types.hpp"
#include "Core/UUID.hpp"

namespace BillyEngine {

struct TransformComponent {
    glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

    glm::mat4 GetTransform() const {
        return glm::translate(glm::mat4(1.0f), Translation) *
               glm::toMat4(glm::quat(Rotation)) *
               glm::scale(glm::mat4(1.0f), Scale);
    }

    TransformComponent() = default;
    BE_DEFAULT_COPY_AND_MOVE(TransformComponent)
};

struct TagComponent {
    std::string Tag;

    TagComponent(std::string_view tag) : Tag(tag.data()) {}
    BE_DEFAULT_COPY_AND_MOVE(TagComponent)
};

struct IDComponent {
    UUID ID() { return m_ID; }

    IDComponent() = default;
    BE_DEFAULT_COPY_AND_MOVE(IDComponent)

   private:
    UUID m_ID;
};

struct SpriteComponent {
    // TODO: Implement this
};

}  // namespace BillyEngine