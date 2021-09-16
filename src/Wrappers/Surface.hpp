#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

class Surface {
   public:
    Surface(glm::ivec2 size);
    explicit Surface(SDL_Surface* surface);

    BE_NON_COPY_CONSTRUCTIBLE(Surface)
    Surface(Surface&& other);
    Surface& operator=(Surface&& other);

    inline SDL_Surface* AsSDLSurface() { return m_Surface; }

    ~Surface();

   private:
    SDL_Surface* m_Surface = nullptr;
};

}  // namespace BillyEngine