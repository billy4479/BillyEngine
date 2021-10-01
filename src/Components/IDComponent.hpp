#pragma once

#include "../Core/Common.hpp"
#include "../Core/UUID.hpp"

namespace BillyEngine {
namespace Components {

class ID {
   public:
    ID() = default;
    ID(UUID id) : m_UUID(id) {}
    inline operator UUID() const { return m_UUID; }

   private:
    UUID m_UUID;
};

}  // namespace Components
}  // namespace BillyEngine