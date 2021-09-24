#include "AssetManager.hpp"

#include "../Application.hpp"
#include "../Wrappers/Font.hpp"
#include "../Wrappers/Surface.hpp"
#include "Common.hpp"

namespace BillyEngine {

AssetManager::AssetManager(std::filesystem::path assetFolder) {
    BE_PROFILE_FUNCTION();

    SetAssetFolder(assetFolder);
}

Ref<Font> AssetManager::LoadFont(const std::filesystem::path &path,
                                 const std::string &name, u32 size) {
    auto font = CreateRef<Font>((m_AssetsFolder / path), size);

    [[maybe_unused]] auto result = m_Fonts.emplace(name, font);
    BE_ASSERT(result.second);

    return font;
}

Ref<Font> AssetManager::GetFont(const std::string &name) {
    auto font = m_Fonts[name];
    BE_ASSERT(font != nullptr);
    return font;
}

AssetManager::~AssetManager() { ReleaseSDLDependencies(); }

void AssetManager::SetAssetFolder(const std::filesystem::path &path) {
    if (path.is_relative())
        m_AssetsFolder = m_BasePath / path;
    else
        m_AssetsFolder = path;
}

std::filesystem::path AssetManager::GetAssetFolder() { return m_AssetsFolder; }

void AssetManager::ReleaseSDLDependencies() {
    // The first one is for the vector, the second is for `font` created in
    // the for loop

#ifdef DEBUG
    for (auto font : m_Fonts) BE_ASSERT(font.second.use_count() == 2);
    for (auto surface : m_Surfaces) BE_ASSERT(surface.second.use_count() == 2);
#endif

    m_Fonts.clear();
    m_Surfaces.clear();
}

std::filesystem::path AssetManager::GetBasePath() {
// TODO: Check if works on windows
#ifdef BE_PLATFORM_WINDOWS
    wchar_t path[MAX_PATH] = {0};
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return std::filesystem::path(path).parent_path();
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    auto p = std::string(result, (size_t)((count > 0) ? count : 0));
    return std::filesystem::path(p).parent_path();
#endif
}

Ref<Surface> AssetManager::LoadImage(const std::filesystem::path &path,
                                     const std::string name) {
    auto s = CreateRef<Surface>(IMG_Load(path.c_str()));

    [[maybe_unused]] auto result = m_Surfaces.emplace(name, s);
    BE_ASSERT(result.second);

    return s;
}

Ref<Surface> AssetManager::GetImage(const std::string &name) {
    auto surface = m_Surfaces[name];
    BE_ASSERT(surface != nullptr);
    return surface;
}
}  // namespace BillyEngine