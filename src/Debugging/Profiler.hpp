#pragma once

#include "../Core/STDInclude.hpp"

#if defined(DEBUG) && defined(BE_USE_PROFILER)

namespace BillyEngine {

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> Start;

    std::string ScopeName;

    Timer(std::string_view scopeName);

    ~Timer();
};

}  // namespace BillyEngine

    #define BE_PROFILE_SCOPE() Timer timer(__PRETTY_FUNCTION__)

#else
    #define BE_PROFILE_SCOPE()
#endif
