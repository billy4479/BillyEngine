#pragma once

#include <filesystem>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "Assets/Asset.hpp"
#include "Core/Logger.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class AssetManager {
   public:
    AssetManager();
    ~AssetManager();

    std::filesystem::path GetBaseDir();
    void SetBaseDir(std::filesystem::path);

    template <typename T, typename... Args>
    Ref<T> Load(std::filesystem::path path, const std::string& name,
                Args... args) {
        static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");
        auto n = std::string(name);

        if (m_Assets.contains(n)) {
            Logger::Core()->error(
                "An asset named {} is already present. Asset at {} will not be "
                "loaded",
                name, path.string());
            return nullptr;
        }

        Ref<T> asset = T::Load(m_BaseDir / path, std::forward<Args>(args)...);
        m_Assets[n] = std::static_pointer_cast<Asset>(asset);
        return asset;
    }

    template <typename T>
    Ref<T> Get(const std::string& name) {
        Ref<Asset> asset = m_Assets.at(name);
        if (asset->GetAssetType() != T::GetAssetTypeStatic()) {
            Logger::Core()->error("Asset {} is not of type {} but {}", name,
                                  T::GetAssetTypeStatic(),
                                  GetAssetTypeName(asset->GetAssetType()));
            return nullptr;
        }

        return std::static_pointer_cast<T>(asset);
    }

    void Unload(const std::string& name);

   private:
    std::filesystem::path m_BaseDir;
    std::unordered_map<std::string, Ref<Asset>> m_Assets;
};

}  // namespace BillyEngine