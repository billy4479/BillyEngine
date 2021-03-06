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

    template <typename T, bool FromMemory = false, typename... Args,
              typename Source>
    Ref<T> Load(Source src, const std::string& name, Args... args) {
        static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");

        if (m_Assets.contains(name)) {
            Logger::Core()->error(
                "An asset named {} is already present. Asset at {} will "
                "not be "
                "loaded",
                name, src);
            return nullptr;
        }

        Ref<T> asset = LoadNoStore<T, FromMemory>(std::forward<Source>(src),
                                                  std::forward<Args>(args)...);

        m_Assets[name] = std::static_pointer_cast<Asset>(asset);
    }

    template <typename T, bool FromMemory = false, typename... Args,
              typename Source>
    Ref<T> LoadNoStore(Source src, Args... args) {
        static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");

        Ref<T> asset;
        if constexpr (FromMemory) {
            asset =
                T::template Load<FromMemory>(src, std::forward<Args>(args)...);
        } else {
            asset = T::template Load<FromMemory>(m_BaseDir / src,
                                                 std::forward<Args>(args)...);
        }

        return asset;
    }

    template <typename T>
    Ref<T> Get(const std::string& name) const {
        Ref<Asset> asset = m_Assets.at(name);
        if (asset->GetAssetType() != std::declval<T>().GetAssetType()) {
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

    // template <typename T, bool FromMemory, typename... Args, typename Source>
    // inline Ref<T> LoadFromType(Source src, Args... args) {
    //     Ref<T> asset;
    //     if constexpr (FromMemory) {
    //         asset =
    //             T::template Load<FromMemory>(src,
    //             std::forward<Args>(args)...);
    //     } else {
    //         asset = T::template Load<FromMemory>(m_BaseDir / src,
    //                                              std::forward<Args>(args)...);
    //     }
    //     return asset;
    // }
};

}  // namespace BillyEngine