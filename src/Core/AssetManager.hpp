#pragma once

#include "Common.hpp"

namespace BillyEngine {

class AssetManager {
   public:
    explicit AssetManager(std::filesystem::path assetFolder = "");
    AssetManager(const AssetManager &) = delete;
    ~AssetManager();

    void SetAssetFolder(const std::filesystem::path &);
    std::filesystem::path GetAssetFolder();

    TTF_Font *LoadFont(const std::filesystem::path &, const std::string &, u32);
    TTF_Font *GetFont(const std::string &);

    SDL_Surface *LoadImage(const std::filesystem::path &, const std::string);
    SDL_Surface *GetImage(const std::string &);

    void ReleaseSDLModules();

   private:
    // https://stackoverflow.com/questions/1528298/get-path-of-executable
    std::filesystem::path GetBasePath();

    std::filesystem::path m_AssetsFolder{""};
    const std::filesystem::path m_BasePath = GetBasePath();
    std::map<const std::string, TTF_Font *> m_Fonts{};
    std::map<const std::string, SDL_Surface *> m_Surfaces{};
};
}  // namespace BillyEngine