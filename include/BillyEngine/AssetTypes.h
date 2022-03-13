#pragma once

#include "EnumerateAssetTypes.h"

#define o(n) AssetType##n,
enum Keys { ENUMERATE_ASSET_TYPES(o) };
#undef o

#undef ENUMERATE_ASSET_TYPES