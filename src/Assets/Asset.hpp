#pragma once

#include "AssetType.hpp"

namespace BillyEngine {

class Asset {
   public:
    virtual AssetType GetAssetType() = 0;
};

}  // namespace BillyEngine