#pragma once

#ifndef NDEBUG
    #define DEBUG 1
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <any>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <entt/entt.hpp>
#include <filesystem>
#include <functional>
#include <glm/ext/vector_int2.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
    #include <windows.h>  //GetModuleFileNameW
#else
    #include <limits.h>
    #include <unistd.h>  //readlink
#endif

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
using f64 = double;

using size_t = __SIZE_TYPE__;

#ifdef DEBUG
    #include <cstdio>
    #define dbg_print(...) fprintf(stderr, __VA_ARGS__)
#else
    #define dbg_print(...) 0
#endif
