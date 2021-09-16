#include "TextComponent.hpp"

#include "../Wrappers/Font.hpp"
#include "../Wrappers/Texture.hpp"

namespace BillyEngine {
namespace Components {

Text::Text(const std::string& text, Ref<Font> font, const Color& color)
    : m_Content(text), m_Font(font), m_Color(color) {}

void Text::SetText(const std::string& text) {
    m_Content = text;
    m_Texture = nullptr;
}

void Text::SetColor(const Color& color) {
    m_Color = color;
    m_Texture = nullptr;
}

const std::string& Text::GetText() const { return m_Content; }
}  // namespace Components
}  // namespace BillyEngine