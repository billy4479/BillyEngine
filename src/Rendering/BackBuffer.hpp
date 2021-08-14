#pragma once
#include <SDL2/SDL.h>

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

class BackBuffer {
   public:
    BackBuffer() = default;
    ~BackBuffer();

    void Init(i32 width, i32 height, SDL_Renderer *renderer);
    void Clear(Color c);
    void Swap();
    u32 &At(i32 x, i32 y);
    void PutTexture(SDL_Texture *, SDL_Rect *);
    void DeleteTexture(SDL_Texture *texture);

   private:
    SDL_Texture *m_Texture = nullptr;
    SDL_Renderer *m_Renderer = nullptr;
    u32 *m_BackBuffer = nullptr;
    i32 m_Width, m_Height, m_Pitch;
    std::vector<std::pair<SDL_Texture *, SDL_Rect *>> m_Textures;
};

}  // namespace BillyEngine
