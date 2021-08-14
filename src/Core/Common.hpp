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
#include <entt/entt.hpp>
#include <filesystem>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using f32 = float;
using f64 = double;

using size_t = __SIZE_TYPE__;

#ifdef DEBUG
    #include <cstdio>
    #define dbg_print(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg_print(...) 0
#endif
