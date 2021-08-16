#include "AssetManager.hpp"

#include "../Application.hpp"
#include "Common.hpp"

namespace BillyEngine {

void AssetManager::LoadFont(const std::filesystem::path &path,
                            const std::string &name, u32 size) {
    auto font = TTF_OpenFont((m_AssetsFolder / path).string().c_str(), size);
    assert(font != nullptr);
    m_Fonts.emplace(name, font);

    PrintInfo();
}

TTF_Font *AssetManager::GetFont(const std::string &name) {
#ifdef DEBUG
    try {
        m_Fonts.at(name);
    } catch (std::out_of_range &e) {
        assert(false);
    }
#endif
    auto font = m_Fonts[name];
    assert(font != nullptr);
    return font;
}

AssetManager::~AssetManager() { ReleaseSDLModules(); }

void AssetManager::SetAssetFolder(const std::filesystem::path &path) {
    if (path.is_relative())
        m_AssetsFolder = m_BasePath / path;
    else
        m_AssetsFolder = path;
}

std::filesystem::path AssetManager::GetAssetFolder() { return m_AssetsFolder; }

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

std::filesystem::path AssetManager::GetBasePath() {
    // TODO: Check if works on windows
#ifdef _WIN32
    wchar_t path[MAX_PATH] = {0};
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return std::filesystem::path(path).parent_path();
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    auto p = std::string(result, (count > 0) ? count : 0);
    return std::filesystem::path(p).parent_path();
#endif
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
}  // namespace BillyEngine