#include "AssetManager.hpp"

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "../Application.hpp"
#include "Common.hpp"

void AssetManager::LoadFont(const std::filesystem::path &path,
                            const std::string &name, u32 size) {
    auto font = TTF_OpenFont((m_AssetsFolder / path).string().c_str(), size);
    assert(font != nullptr);
    m_Fonts.emplace(name, font);
}

TTF_Font *AssetManager::GetFont(const std::string &name) {
    auto font = m_Fonts[name];
    assert(font != nullptr);
    return font;
}

AssetManager::~AssetManager() { ReleaseSDLModules(); }

void AssetManager::ReleaseSDLModules() {
    if (!m_Fonts.empty()) {
        for (auto font : m_Fonts) {
            if (font.second != nullptr) {
                TTF_CloseFont(font.second);
                font.second = nullptr;
            }
        }

        m_Fonts.clear();
    }

    if (!m_Textures.empty()) {
        for (auto texture : m_Textures) {
            SDL_DestroyTexture(texture.second);
            texture.second = nullptr;
        }

        m_Textures.clear();
    }
}

void AssetManager::LoadImage(const std::filesystem::path &path,
                             const std::string name) {
    assert(m_Textures.find(name) == m_Textures.end());
    auto s = IMG_Load(path.c_str());
    assert(s != nullptr);

    m_Textures.emplace("name", SDL_CreateTextureFromSurface(
                                   m_App->GetRenderer()->GetSDLRenderer(), s));

    SDL_FreeSurface(s);
}