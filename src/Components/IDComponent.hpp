#pragma once

#include "../Core/Common.hpp"
#include "../Core/UUID.hpp"

namespace BillyEngine {
namespace Components {

class ID {
   public:
    ID() = default;
    inline operator UUID() const { return m_UUID; }

   private:
    UUID m_UUID;
};

}  // namespace Components
}  // namespace BillyEngine