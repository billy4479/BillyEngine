#pragma once

#include <spdlog/spdlog.h>

#include <array>

#include "Types.hpp"

namespace BillyEngine {

class Logger {
   public:
    static Logger& The();

    Ref<spdlog::logger> EngineLogger() { return m_EngineLogger; }
    Ref<spdlog::logger> ClientLogger() { return m_ClientLogger; }

   private:
    Logger();

    static Logger* s_Instance;

    Ref<spdlog::logger> m_EngineLogger;
    Ref<spdlog::logger> m_ClientLogger;

    std::array<spdlog::sink_ptr, 2> m_Sinks;
};

// clang-format off
#define BE_CORE_TRACE(...)    Logger::The().EngineLogger()->trace(__VA_ARGS__)
#define BE_CORE_INFO(...)     Logger::The().EngineLogger()->info(__VA_ARGS__)
#define BE_CORE_WARN(...)     Logger::The().EngineLogger()->warn(__VA_ARGS__)
#define BE_CORE_ERROR(...)    Logger::The().EngineLogger()->error(__VA_ARGS__)
#define BE_CORE_CRITICAL(...) Logger::The().EngineLogger()->critical(__VA_ARGS__)

#define BE_TRACE(...)         Logger::The().ClientLogger()->trace(__VA_ARGS__)
#define BE_INFO(...)          Logger::The().ClientLogger()->info(__VA_ARGS__)
#define BE_WARN(...)          Logger::The().ClientLogger()->warn(__VA_ARGS__)
#define BE_ERROR(...)         Logger::The().ClientLogger()->error(__VA_ARGS__)
#define BE_CRITICAL(...)      Logger::The().ClientLogger()->critical(__VA_ARGS__)

// clang-format on 

}