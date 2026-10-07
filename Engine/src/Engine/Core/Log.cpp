#include "Engine/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace RealEngine {

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
    // [timestamp] logger-name: message, with level colouring.
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("REALENGINE");
    s_CoreLogger->set_level(spdlog::level::trace);
    s_CoreLogger->flush_on(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
    s_ClientLogger->flush_on(spdlog::level::trace);
}

} // namespace RealEngine
