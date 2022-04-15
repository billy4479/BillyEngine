#pragma once

#include "AssetType.hpp"

namespace BillyEngine {

class Asset {
   public:
    virtual AssetType GetAssetType() const = 0;
};

}  // namespace BillyEngine