#include <thread>

#include "../Core/Common.hpp"

// This later
#include "Assert.hpp"
#include "Profiler.hpp"

#if defined(DEBUG) && defined(BE_USE_PROFILER)

namespace BillyEngine {

Timer::Timer(std::string_view scopeName) : ScopeName(scopeName) {
    Start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    auto End = std::chrono::high_resolution_clock::now();

    u64 start = std::chrono::time_point_cast<std::chrono::microseconds>(Start)
                    .time_since_epoch()
                    .count();
    u64 end = std::chrono::time_point_cast<std::chrono::microseconds>(End)
                  .time_since_epoch()
                  .count();
    auto tid = std::this_thread::get_id();

    Profiler::The().WriteProfile(ProfileResult{
        ScopeName, start, end, std::hash<std::thread::id>{}(tid)});
}

Profiler Profiler::s_Instance = Profiler();
Profiler& Profiler::The() { return s_Instance; }

Profiler::~Profiler() {
    BE_ASSERT(m_OutputStream.is_open());

    // Write footer
    m_OutputStream << "]}";

    // Close file
    m_OutputStream.close();

    BE_CORE_TRACE("Profiler recorded {} entries", m_ProfileCount);
}

void Profiler::WriteProfile(const ProfileResult& result) {
    BE_ASSERT(m_OutputStream.is_open());

    // Serialize data
    if (m_ProfileCount++ > 0) m_OutputStream << ",";

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    m_OutputStream << "{";
    m_OutputStream << "\"cat\":\"function\",";
    m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
    m_OutputStream << "\"name\":\"" << name << "\",";
    m_OutputStream << "\"ph\":\"X\",";
    m_OutputStream << "\"pid\":0,";
    m_OutputStream << "\"tid\":" << result.ThreadID << ",";
    m_OutputStream << "\"ts\":" << result.Start;
    m_OutputStream << "}";

    m_OutputStream.flush();
}

Profiler::Profiler() {
    // Open file
    m_OutputStream.open("ProfilerResult.json");
    BE_ASSERT(m_OutputStream.is_open());

    // Write header
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputStream.flush();
}

}  // namespace BillyEngine

#endif
