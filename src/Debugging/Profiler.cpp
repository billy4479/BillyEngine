#include "../Core/Common.hpp"

// This later
#include "Profiler.hpp"

#if defined(DEBUG) && defined(BE_USE_PROFILER)

namespace BillyEngine {

Timer::Timer(std::string_view scopeName) : ScopeName(scopeName) {
    Start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    auto End = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(Start)
                     .time_since_epoch()
                     .count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(End)
                   .time_since_epoch()
                   .count();

    f64 time = (f32)(end - start) / 1000.0f;

    BE_CORE_TRACE("{} took {}ms", ScopeName.data(), time);
}
}  // namespace BillyEngine

#endif
