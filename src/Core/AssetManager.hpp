#pragma once

#include "Common.hpp"

namespace BillyEngine {
class Application;

class AssetManager {
   public:
    explicit AssetManager(Application *a) : m_App(a) {}
    AssetManager(const AssetManager &) = delete;
    ~AssetManager();

    void SetAssetFolder(const std::filesystem::path &);
    std::filesystem::path GetAssetFolder();

    void LoadFont(const std::filesystem::path &, const std::string &, u32);
    TTF_Font *GetFont(const std::string &);

    void LoadImage(const std::filesystem::path &, const std::string);

    void ReleaseSDLModules();

   private:
    // https://stackoverflow.com/questions/1528298/get-path-of-executable
    std::filesystem::path GetBasePath();

    Application *m_App = nullptr;
    std::filesystem::path m_AssetsFolder{""};
    const std::filesystem::path m_BasePath = GetBasePath();
    std::map<const std::string, TTF_Font *> m_Fonts{};
    std::map<const std::string, SDL_Texture *> m_Textures{};
};
}  // namespace BillyEngine