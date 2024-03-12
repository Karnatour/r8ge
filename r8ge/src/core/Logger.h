#pragma once

#include "Core.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace r8ge {
    class Logger;
    namespace global {
    extern Logger* logger;
}
    class Logger{
    public:
        Logger();
        ~Logger();
        void logLoop();
        void init();
        static std::shared_ptr<spdlog::logger>& getLogger() { return s_Logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
        std::thread m_thread;
        std::mutex m_mutex;
        bool m_running;
    };
}

#define R8GE_LOG_TRACE(...) ::r8ge::Logger::getLogger()->trace(__VA_ARGS__)
#define R8GE_LOG_INFOR(...) ::r8ge::Logger::getLogger()->info(__VA_ARGS__)
#define R8GE_LOG_DEBUG(...) ::r8ge::Logger::getLogger()->debug(__VA_ARGS__)
#define R8GE_LOG_WARNI(...) ::r8ge::Logger::getLogger()->warn(__VA_ARGS__)
#define R8GE_LOG_ERROR(...) ::r8ge::Logger::getLogger()->error(__VA_ARGS__)
#define R8GE_LOG_FATAL(...) ::r8ge::Logger::getLogger()->critical(__VA_ARGS__)

#define R8GE_LOG(...) R8GE_LOG_TRACE(__VA_ARGS__)

