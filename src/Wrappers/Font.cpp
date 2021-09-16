#include "Font.hpp"

namespace BillyEngine {
Font::Font(std::filesystem::path path, i32 size) {
    m_Font = TTF_OpenFont(path.c_str(), size);
    BE_CHECK_SDL_ERROR_AND_DIE();
    BE_ASSERT(m_Font != nullptr);
}
Font::Font(TTF_Font* font) : m_Font(font) {
    BE_CHECK_SDL_ERROR_AND_DIE();
    BE_ASSERT(m_Font != nullptr);
}
Font::Font(Font&& other) {
    this->m_Font = other.m_Font;
    other.m_Font = nullptr;
}
Font& Font::operator=(Font&& other) {
    if (this != &other) {
        this->m_Font = other.m_Font;
        other.m_Font = nullptr;
    }
    return *this;
}
Font::~Font() {
    TTF_CloseFont(m_Font);
    BE_CHECK_SDL_ERROR_AND_DIE();
}
}  // namespace BillyEngine