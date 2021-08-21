#include "AssetManager.hpp"

#include "../Application.hpp"
#include "Common.hpp"

namespace BillyEngine {

AssetManager::AssetManager(std::filesystem::path assetFolder) {
    SetAssetFolder(assetFolder);
}

TTF_Font *AssetManager::LoadFont(const std::filesystem::path &path,
                                 const std::string &name, u32 size) {
    auto font = TTF_OpenFont((m_AssetsFolder / path).string().c_str(), size);
    assert(font != nullptr);

    auto result = m_Fonts.emplace(name, font);
    assert(result.second);

    return font;
}

TTF_Font *AssetManager::GetFont(const std::string &name) {
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

    if (!m_Surfaces.empty()) {
        for (auto surface : m_Surfaces) {
            SDL_FreeSurface(surface.second);
            surface.second = nullptr;
        }

        m_Surfaces.clear();
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

SDL_Surface *AssetManager::LoadImage(const std::filesystem::path &path,
                                     const std::string name) {
    auto s = IMG_Load(path.c_str());
    assert(s != nullptr);

    auto result = m_Surfaces.emplace(name, s);
    assert(result.second);

    return s;
}

SDL_Surface *AssetManager::GetImage(const std::string &name) {
    auto surface = m_Surfaces[name];
    assert(surface != nullptr);
    return surface;
}
}  // namespace BillyEngine