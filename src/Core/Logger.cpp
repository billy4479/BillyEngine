#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Types.hpp"

namespace BillyEngine {

Logger* Logger::s_Instance{nullptr};

#if BE_GL_DEBUG
bool Logger::LogGLEnabled{true};
#endif

void Logger::CreateOrReset() {
    if (s_Instance) delete s_Instance;

    s_Instance = new Logger();

#if BE_GL_DEBUG
    LogGLEnabled = true;
#endif
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

    m_ClientLogger =
        std::make_shared<spdlog::logger>("APP", begin(m_Sinks), end(m_Sinks));
    spdlog::register_logger(m_ClientLogger);
    m_ClientLogger->set_level(spdlog::level::trace);
    m_ClientLogger->flush_on(spdlog::level::trace);
}
}  // namespace BillyEngine