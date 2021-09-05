#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {

struct Font {
    Font(std::filesystem::path path, i32 size) {
        m_Font = TTF_OpenFont(path.c_str(), size);
        BE_ASSERT(m_Font != nullptr);
    }
    explicit Font(TTF_Font* font) : m_Font(font) {
        BE_ASSERT(m_Font != nullptr);
    }

    BE_NON_COPY_CONSTRUTIBLE(Font)
    Font(Font&& other) {
        this->m_Font = other.m_Font;
        other.m_Font = nullptr;
    }
    Font& operator=(Font&& other) {
        if (this != &other) {
            this->m_Font = other.m_Font;
            other.m_Font = nullptr;
        }
        return *this;
    }

    inline TTF_Font* AsSDLFont() { return m_Font; }

    ~Font() { TTF_CloseFont(m_Font); }

   private:
    TTF_Font* m_Font = nullptr;
};

}  // namespace BillyEngine