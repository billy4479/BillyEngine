#pragma once

#include <SDL2/SDL.h>

#include "Common.hpp"

class EventHandler {
   public:
    void HandleEvents();
    bool ShouldClose();

   private:
    bool m_ShouldClose = false;
};