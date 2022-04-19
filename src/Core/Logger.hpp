#pragma once

#include <spdlog/spdlog.h>

#include <array>

#include "Core/Types.hpp"

namespace BillyEngine {

class Logger {
   public:
    static Ref<spdlog::logger> Core() {
        assert(s_Instance);
        return s_Instance->m_CoreLogger;
    }
    static Ref<spdlog::logger> Client() {
        assert(s_Instance);
        return s_Instance->m_ClientLogger;
    }

    static void CreateOrReset();

    ~Logger();
#if BE_GL_DEBUG
    static bool LogGLEnabled;
#endif

   private:
    Logger();

    static Logger* s_Instance;

    Ref<spdlog::logger> m_CoreLogger;
    Ref<spdlog::logger> m_ClientLogger;

    std::array<spdlog::sink_ptr, 2> m_Sinks;
};

#if BE_GL_DEBUG
    #include <spdlog/fmt/fmt.h>
    #define BE_GL_LOG(...)                                                   \
        {                                                                    \
            if (Logger::LogGLEnabled)                                        \
                Logger::Core()->debug("[GL]: {}", fmt::format(__VA_ARGS__)); \
        }
#else
    #define BE_GL_LOG(...)
#endif

// // clang-format off
// #define BE_CORE_TRACE(...)    Logger::Engine()->trace(__VA_ARGS__)
// #define BE_CORE_INFO(...)     Logger::Engine()->info(__VA_ARGS__)
// #define BE_CORE_WARN(...)     Logger::Engine()->warn(__VA_ARGS__)
// #define BE_CORE_ERROR(...)    Logger::Engine()->error(__VA_ARGS__)
// #define BE_CORE_CRITICAL(...) Logger::Engine()->critical(__VA_ARGS__)

// #define BE_TRACE(...)         Logger::Client()->trace(__VA_ARGS__)
// #define BE_INFO(...)          Logger::Client()->info(__VA_ARGS__)
// #define BE_WARN(...)          Logger::Client()->warn(__VA_ARGS__)
// #define BE_ERROR(...)         Logger::Client()->error(__VA_ARGS__)
// #define BE_CRITICAL(...)      Logger::Client()->critical(__VA_ARGS__)

// // clang-format on

}  // namespace BillyEngine
