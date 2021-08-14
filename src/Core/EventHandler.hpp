#pragma once

#include "Common.hpp"

namespace BillyEngine {
class EventHandler {
   public:
    void HandleEvents();
    bool ShouldClose();

   private:
    bool m_ShouldClose = false;
};
}  // namespace BillyEngine