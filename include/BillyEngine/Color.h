#pragma once

#include <stdint.h>

#include "Utils.h"

struct Color;

BE_HEADER_START

BE_PUBLIC Color* ColorFromRGBA32F(float, float, float, float = 1);
BE_PUBLIC Color* ColorFromRGBA32(uint32_t);
BE_PUBLIC Color* ColorFromRGBA(uint8_t, uint8_t, uint8_t, uint8_t = 0xff);

BE_PUBLIC void ColorToRGBA32F(Color*, float*, float*, float*, float*);
BE_PUBLIC void ColorToRGBA32(Color*, uint32_t*);
BE_PUBLIC void ColorToRGBA(Color*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);

BE_HEADER_END