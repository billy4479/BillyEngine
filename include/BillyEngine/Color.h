#pragma once

#include <stdint.h>

#include "Utils.h"

struct Color;

BE_HEADER_START

BE_API Color* ColorFromRGBA32F(float, float, float, float = 1);
BE_API Color* ColorFromRGBA32(uint32_t);
BE_API Color* ColorFromRGBA(uint8_t, uint8_t, uint8_t, uint8_t = 0xff);

BE_API void ColorToRGBA32F(Color*, float*, float*, float*, float*);
BE_API void ColorToRGBA32(Color*, uint32_t*);
BE_API void ColorToRGBA(Color*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);

BE_HEADER_END