/**
 * @file DrawableTexture.hpp
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"
#include "../Wrappers/Surface.hpp"
#include "../Wrappers/Texture.hpp"

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
    inline bool HasTexture() const { return m_HasTexture; }

    /**
     * @brief Get `Ref<Texture>` if has been generated
     *
     * Return the `Ref<Texture>` that was generated
     * in `Finalize`.
     *
     * It will fail if the texture wasn't finalized.
     *
     * @return Ref<Texture> of the drawn pixel data
     */
    inline Ref<Texture> GetTexture() {
        BE_ASSERT(m_HasTexture);
        return m_Texture;
    }

    inline Ref<Texture> GetTextureOrNull() { return m_Texture; }

    /**
     * @brief Finalize and get the just generated `Ref<Texture>`
     *
     * `Finalize` gets called
     * and the generated texture is returned.
     *
     * @return Ref<Texture> of the drawn pixel data
     */
    inline Ref<Texture> FinalizeAndGetTexture() {
        Finalize();
        return m_Texture;
    }

   public:
    /**
     * @brief Create a new `DrawableTexture` object
     *
     * @param renderer The current renderer
     * @param size The size of the texture
     */
    DrawableTexture(Ref<Renderer> renderer, glm::ivec2 size);
    // DrawableTexture() = default;
    /**
     * @brief Create a new `DrawableTexture` from an existing `Surface`
     *
     * @param surface The base texture
     */
    DrawableTexture(Ref<Surface> surface, Ref<Renderer> renderer)
        : m_Renderer(renderer), m_Surface(surface) {}

    ~DrawableTexture() = default;

   private:
    Ref<Renderer> m_Renderer = nullptr;
    Ref<Surface> m_Surface = nullptr;
    Ref<Texture> m_Texture = nullptr;
    glm::ivec2 m_Size{0, 0};
    bool m_HasTexture = false;
};
}  // namespace BillyEngine