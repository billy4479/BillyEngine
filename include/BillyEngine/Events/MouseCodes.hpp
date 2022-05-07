#pragma once

#include "Core/Types.hpp"
#include "Enumerate/EnumerateMouseButtons.h"

namespace BillyEngine {

using MouseCode = i8;
namespace Buttons {

#define o(k, n) k = n,
enum : MouseCode { ENUMERATE_MOUSE_BUTTONS(o) };
#undef o

}  // namespace Buttons
}  // namespace BillyEngine

#undef ENUMERATE_MOUSE_BUTTONS
