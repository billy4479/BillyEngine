// #include "Label.hpp"

// #include <SDL2/SDL_ttf.h>

// #include "../Core/AssetManager.hpp"
// #include "../Core/Color.hpp"

// namespace Entity {

// Label::Label(Application *application, const std::string &font_name,
//              const std::string &text, std::pair<i32, i32> position)
//     : m_Application(application),
//       m_font_name(font_name),
//       m_text(text),
//       m_position(SDL_Rect{position.first, position.second, 0, 0}) {
//     assert(m_Application != nullptr);
//     SetText(text);
//     m_Application->GetRenderer()->PutTexture(m_texture, &m_position);
// }

// void Label::SetText(const std::string &text) {
//     assert(m_Application->GetRenderer() != nullptr);
//     assert(m_Application->GetRenderer()->GetSDLRenderer() != nullptr);
//     assert(m_Application->GetAssetManager() != nullptr);

//     auto font = m_Application->GetAssetManager()->GetFont(m_font_name);
//     assert(font != nullptr);

//     auto tmp_surf = TTF_RenderText_Blended(font, text.c_str(), Color::white);
//     assert(tmp_surf != nullptr);

//     m_texture = SDL_CreateTextureFromSurface(
//         m_Application->GetRenderer()->GetSDLRenderer(), tmp_surf);
//     SDL_FreeSurface(tmp_surf);
//     assert(m_texture != nullptr);

//     SDL_QueryTexture(m_texture, nullptr, nullptr, &m_position.w,
//     &m_position.h);
// }

// Label::~Label() {
//     m_Application->GetRenderer()->DeleteTexture(m_texture);
//     SDL_DestroyTexture(m_texture);
// }

// }  // namespace Entity
