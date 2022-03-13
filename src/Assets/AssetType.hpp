#pragma once

#include <BillyEngine/EnumerateAssetTypes.h>

#include <string_view>

namespace BillyEngine {

#define o(n) n,
enum class AssetType { ENUMERATE_ASSET_TYPES(o) };
#undef o

#define o(n)           \
    case AssetType::n: \
        return #n;

inline constexpr std::string_view GetAssetTypeName(AssetType assetType) {
    switch (assetType) { ENUMERATE_ASSET_TYPES(o) }
}
#undef o

}  // namespace BillyEngine

#undef ENUMERATE_ASSET_TYPES