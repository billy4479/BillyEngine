#include "Core/Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Core/Types.hpp"

namespace BillyEngine {

Logger* Logger::s_Instance{nullptr};

void Logger::CreateOrReset() {
    if (s_Instance) delete s_Instance;

    s_Instance = new Logger();
}

Logger::~Logger() { spdlog::drop_all(); }

Logger::Logger() {
    m_Sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    m_Sinks[1] = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "BillyEngine.log", true);

    m_Sinks[0]->set_pattern("%^[%T] %n: %v%$");
    m_Sinks[1]->set_pattern("[%T] [%l] %n: %v");

    m_CoreLogger =
        std::make_shared<spdlog::logger>("CORE", begin(m_Sinks), end(m_Sinks));
    spdlog::register_logger(m_CoreLogger);
    m_CoreLogger->set_level(spdlog::level::trace);
    m_CoreLogger->flush_on(spdlog::level::trace);

#if BE_GL_LOG
    m_GLLogger =
        std::make_shared<spdlog::logger>("GL", begin(m_Sinks), end(m_Sinks));
    spdlog::register_logger(m_GLLogger);
    m_GLLogger->set_level(spdlog::level::trace);
    m_GLLogger->flush_on(spdlog::level::trace);
#endif

    m_ClientLogger =
        std::make_shared<spdlog::logger>("APP", begin(m_Sinks), end(m_Sinks));
    spdlog::register_logger(m_ClientLogger);
    m_ClientLogger->set_level(spdlog::level::trace);
    m_ClientLogger->flush_on(spdlog::level::trace);
}
}  // namespace BillyEngine