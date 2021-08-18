/**
 * @file DrawableTexture.hpp
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"

namespace BillyEngine {

/**
 * @brief A simple wrapper around SDL_Surface
 *
 * Drawable texture is just a `SDL_Surface`
 * with some useful methods added on it
 * like `PutPixel` and `Clear`.
 *
 * It also handles the conversion to `SDL_Texture` with
 * the `Finalize` method.
 *
 */
class DrawableTexture {
   public:
    /**
     * @brief Color a pixel on the texture
     *
     * @param position A `glm::ivec2` with the coordinates of the pixel
     * @param c The color the pixel will be set to
     */
    void PutPixel(glm::ivec2 position, const Color& c);

    /**
     * @brief Set all the pixel to a color
     *
     * Set all the pixel of the texture to `c`
     *
     * @param c The color
     */
    void Clear(const Color& c);

    /**
     * @brief Write pixel data to the GPU
     *
     * This will generate a SDL_Texture out of the pixel data.
     * If it has been already called it will update the texture
     * with the new data.
     */
    void Finalize();

    /**
     * @brief Check if `Finalize` has been called
     *
     * Checks if the pixel data has already been copied to the GPU.
     *
     * @return true if `Finalize` has been called
     * @return false if `Finalize` has not been called
     */
    inline bool IsFinalized() const { return m_IsFinalized; }

    /**
     * @brief Get `SDL_Texture` if has been generated
     *
     * Return the `SDL_Texture` that was generated
     * in `Finalize`.
     *
     * It will fail if the texture wasn't finalized.
     *
     * @return SDL_Texture* of the drawn pixel data
     */
    SDL_Texture* GetTexture() {
        assert(IsFinalized());
        return m_Texture;
    }

    /**
     * @brief Finalize and get the just generated `SDL_Texture`
     *
     * If hasn't been finalized yet `Finalize` gets called
     * and the generated texture is returned.
     *
     * @return SDL_Texture* of the drawn pixel data
     */
    SDL_Texture* FinalizeAndGetTexture() {
        if (!IsFinalized()) Finalize();
        return m_Texture;
    }

   public:
    /**
     * @brief Create a new `DrawableTexture` object
     *
     * @param renderer A pointer to the current renderer
     * @param size The size of the texture
     */
    DrawableTexture(SDL_Renderer* renderer, glm::ivec2 size);
    /**
     * @brief Create a new `DrawableTexture` from an existing `SDL_Surface`
     *
     * @param surface The base texture. Will be freed in the destructor
     */
    explicit DrawableTexture(SDL_Surface* surface) : m_Surface(surface) {}
    DrawableTexture(DrawableTexture& other) = delete;
    DrawableTexture(DrawableTexture&& other) {
        this->m_Texture = other.m_Texture;
        other.m_Texture = nullptr;
    }
    DrawableTexture& operator=(DrawableTexture&& other) {
        if (this != &other) {
            this->m_Texture = other.m_Texture;
            other.m_Texture = nullptr;
        }
        return *this;
    }
    ~DrawableTexture();

   private:
    SDL_Renderer* m_Renderer = nullptr;
    SDL_Surface* m_Surface = nullptr;
    SDL_Texture* m_Texture = nullptr;
    glm::ivec2 m_Size;
    bool m_IsFinalized = false;
};
}  // namespace BillyEngine