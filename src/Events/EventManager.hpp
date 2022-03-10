#pragma once

#include "../Rendering/Window.hpp"

namespace BillyEngine {

class EventManager {
   public:
    EventManager(Window&);
    ~EventManager();

    void HandleEvents();

   private:
    Window& m_Window;
};

}  // namespace BillyEngine