#pragma once

#include "../Core/Types.hpp"
#include "./EnumerateMouseButtons.h"

namespace BillyEngine {

using MouseCode = u8;
namespace Keys {

#define o(k, n) k = n,
enum : MouseCode { ENUMERATE_MOUSE_BUTTONS(o) };
#undef o

}  // namespace Keys
}  // namespace BillyEngine

#undef ENUMERATE_MOUSE_BUTTONS
