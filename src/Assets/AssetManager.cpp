#include "Assets/AssetManager.hpp"

#include "Core/PlatformDetection.hpp"

#ifdef BE_PLATFORM_WINDOWS
    #include <windows.h>  //GetModuleFileNameW
#else
    #include <limits.h>
    #include <unistd.h>  //readlink
#endif

namespace BillyEngine {

static std::filesystem::path GetExecutableDir() {
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

AssetManager::AssetManager() : m_BaseDir(GetExecutableDir() / "assets") {}
AssetManager::~AssetManager() { m_Assets.clear(); }

void AssetManager::Unload(const std::string& name) {
#if DEBUG
    if (!m_Assets.contains(name))
        Logger::Core()->warn("Asset {} does not exist but is being unloaded",
                             name);
#endif
    m_Assets.erase(name);
}

std::filesystem::path AssetManager::GetBaseDir() { return m_BaseDir; }
void AssetManager::SetBaseDir(std::filesystem::path path) { m_BaseDir = path; }

}  // namespace BillyEngine