#pragma once

#include <BillyEngine/EnumerateKeys.h>

#include "Core/Types.hpp"

namespace BillyEngine {

using KeyCode = u16;
namespace Keys {

#define o(k, n) k = n,
enum : KeyCode { ENUMERATE_KEYS(o) };
#undef o

}  // namespace Keys
}  // namespace BillyEngine

#undef ENUMERATE_KEYS
