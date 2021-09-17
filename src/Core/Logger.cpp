#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace BillyEngine {

Ref<spdlog::logger> Logger::m_EngineLogger;
Ref<spdlog::logger> Logger::m_ClientLogger;

void Logger::Init() {
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "BillyEngine.log", true));

    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    logSinks[1]->set_pattern("[%T] [%l] %n: %v");

    m_EngineLogger = std::make_shared<spdlog::logger>("ENGINE", begin(logSinks),
                                                      end(logSinks));
    spdlog::register_logger(m_EngineLogger);
    m_EngineLogger->set_level(spdlog::level::trace);
    m_EngineLogger->flush_on(spdlog::level::trace);

    m_ClientLogger =
        std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
    spdlog::register_logger(m_ClientLogger);
    m_ClientLogger->set_level(spdlog::level::trace);
    m_ClientLogger->flush_on(spdlog::level::trace);
}
}  // namespace BillyEngine