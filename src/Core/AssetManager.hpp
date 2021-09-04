#pragma once

#include "../Wrappers/Fwd.hpp"
#include "Common.hpp"

namespace BillyEngine {

class AssetManager {
   public:
    explicit AssetManager(std::filesystem::path assetFolder = "");
    ~AssetManager();
    BE_NON_COPY_CONSTRUTIBLE(AssetManager)

    void SetAssetFolder(const std::filesystem::path &);
    std::filesystem::path GetAssetFolder();

    Ref<Font> LoadFont(const std::filesystem::path &, const std::string &, u32);
    Ref<Font> GetFont(const std::string &);

    Ref<Surface> LoadImage(const std::filesystem::path &, const std::string);
    Ref<Surface> GetImage(const std::string &);

    void ReleaseSDLModules();

   private:
    // https://stackoverflow.com/questions/1528298/get-path-of-executable
    std::filesystem::path GetBasePath();

    std::filesystem::path m_AssetsFolder{""};
    const std::filesystem::path m_BasePath = GetBasePath();
    std::map<const std::string, Ref<Font>> m_Fonts{};
    std::map<const std::string, Ref<Surface>> m_Surfaces{};
};
}  // namespace BillyEngine