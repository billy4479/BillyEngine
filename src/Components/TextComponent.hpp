#pragma once

#include "../Core/Color.hpp"
#include "../Core/Common.hpp"
#include "../Wrappers/Fwd.hpp"

namespace BillyEngine {
class EntityManager;

namespace Components {
class Text {
   public:
    Text() = default;
    Text(const std::string& text, Ref<Font> font,
         const Color& color = Color::white);

    void SetText(const std::string& text);
    void SetFont(Ref<Font>);
    void SetColor(const Color& color);

    const std::string& GetText() const;

   private:
    std::string m_Content;
    Ref<Font> m_Font = nullptr;
    Ref<Texture> m_Texture = nullptr;
    Color m_Color = Color::white;

    friend class ::BillyEngine::EntityManager;
};

}  // namespace Components
}  // namespace BillyEngine