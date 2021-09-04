#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"
#include "../Wrappers/Font.hpp"
#include "../Wrappers/Texture.hpp"

namespace BillyEngine {
namespace Components {
struct Text {
    std::string m_Content;
    Ref<Font> m_Font = nullptr;
    Ref<Texture> m_Texture = nullptr;
    Color fgColor;

    Text(const std::string& text, Ref<Font> font,
         const Color& color = Color::white)
        : m_Content(text), m_Font(font), fgColor(color) {}

    void UpdateText(const std::string& text) {
        m_Content = text;
        m_Texture = nullptr;
    }

    void UpdateColor(const Color& color) {
        fgColor = color;
        m_Texture = nullptr;
    }
};

}  // namespace Components
}  // namespace BillyEngine