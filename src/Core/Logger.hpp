#pragma once

#include "Aliases.hpp"
#include "Formatters.hpp"
#include "STDInclude.hpp"

namespace BillyEngine {
class Logger {
   public:
    static void Init();

    static Ref<spdlog::logger> EngineLogger() { return m_EngineLogger; }
    static Ref<spdlog::logger> ClientLogger() { return m_ClientLogger; }

   private:
    Logger() = default;
    static Ref<spdlog::logger> m_EngineLogger;
    static Ref<spdlog::logger> m_ClientLogger;
};
}  // namespace BillyEngine

// clang-format off
#define BE_CORE_TRACE(...)    ::BillyEngine::Logger::EngineLogger()->trace(__VA_ARGS__)
#define BE_CORE_INFO(...)     ::BillyEngine::Logger::EngineLogger()->info(__VA_ARGS__)
#define BE_CORE_WARN(...)     ::BillyEngine::Logger::EngineLogger()->warn(__VA_ARGS__)
#define BE_CORE_ERROR(...)    ::BillyEngine::Logger::EngineLogger()->error(__VA_ARGS__)
#define BE_CORE_CRITICAL(...) ::BillyEngine::Logger::EngineLogger()->critical(__VA_ARGS__)

#define BE_TRACE(...)         ::BillyEngine::Logger::ClientLogger()->trace(__VA_ARGS__)
#define BE_INFO(...)          ::BillyEngine::Logger::ClientLogger()->info(__VA_ARGS__)
#define BE_WARN(...)          ::BillyEngine::Logger::ClientLogger()->warn(__VA_ARGS__)
#define BE_ERROR(...)         ::BillyEngine::Logger::ClientLogger()->error(__VA_ARGS__)
#define BE_CRITICAL(...)      ::BillyEngine::Logger::ClientLogger()->critical(__VA_ARGS__)

// clang-format on 
