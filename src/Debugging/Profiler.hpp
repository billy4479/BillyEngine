#pragma once

#include "../Core/Aliases.hpp"
#include "../Core/PlatformDetection.hpp"
#include "../Core/STDInclude.hpp"
#include "DebugSettings.hpp"

#if defined(DEBUG) && BE_USE_PROFILER

namespace BillyEngine {

struct ProfileResult {
    std::string Name;
    u64 Start, End;
    size_t ThreadID;
};

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> Start;

    std::string ScopeName;

    Timer(std::string_view scopeName);

    ~Timer();
};

class Profiler {
   public:
    static Profiler& The();

    ~Profiler();
    void WriteProfile(const ProfileResult&);

   private:
    Profiler();
    static Profiler s_Instance;
    std::ofstream m_OutputStream;
    u32 m_ProfileCount = 0;
};

}  // namespace BillyEngine

    #define BE_PROFILE_SCOPE(name) Timer timer(name)
    #define BE_PROFILE_FUNCTION() Timer timer(BE_FUNC_SIG)

#else
    #define BE_PROFILE_SCOPE(...)
    #define BE_PROFILE_FUNCTION()
#endif
