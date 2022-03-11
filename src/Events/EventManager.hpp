#pragma once

namespace BillyEngine {

class Window;

class EventManager {
   public:
    EventManager(Window&);
    ~EventManager();

    void HandleEvents();

   private:
    Window& m_Window;
};

}  // namespace BillyEngine