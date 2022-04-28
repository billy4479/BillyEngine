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

#if BE_GL_LOG
    static Ref<spdlog::logger> GL() {
        assert(s_Instance);
        return s_Instance->m_GLLogger;
    }
#endif

    static void CreateOrReset();

    ~Logger();

   private:
    Logger();

    static Logger* s_Instance;

    Ref<spdlog::logger> m_CoreLogger;

#if BE_GL_LOG
    Ref<spdlog::logger> m_GLLogger;
#endif

    Ref<spdlog::logger> m_ClientLogger;

    std::array<spdlog::sink_ptr, 2> m_Sinks;
};

#if BE_GL_DEBUG
    #define BE_LOG_GL_CALL(...) Logger::GL()->trace(__VA_ARGS__)
#else
    #define BE_LOG_GL_CALL(...)
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
