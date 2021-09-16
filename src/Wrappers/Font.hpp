#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {

struct Font {
    Font(std::filesystem::path path, i32 size);
    explicit Font(TTF_Font* font);

    BE_NON_COPY_CONSTRUTIBLE(Font)
    Font(Font&& other);
    Font& operator=(Font&& other);

    inline TTF_Font* AsSDLFont() { return m_Font; }

    ~Font();

   private:
    TTF_Font* m_Font = nullptr;
};

}  // namespace BillyEngine