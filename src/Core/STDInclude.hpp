#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#ifdef _WIN32
    #include <windows.h>  //GetModuleFileNameW
#else
    #include <limits.h>
    #include <unistd.h>  //readlink
#endif
