#pragma once

#include <BillyEngine/EnumerateMouseButtons.h>

#include "../Core/Types.hpp"

namespace BillyEngine {

using MouseCode = u8;
namespace Keys {

#define o(k, n) k = n,
enum : MouseCode { ENUMERATE_MOUSE_BUTTONS(o) };
#undef o

}  // namespace Keys
}  // namespace BillyEngine

#undef ENUMERATE_MOUSE_BUTTONS
