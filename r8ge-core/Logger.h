#ifndef R8GE_LOGGER_H
#define R8GE_LOGGER_H

#include <string>
#include <chrono>
#include <queue>
#include <mutex>

#include "utility/StringFormat.h"

namespace r8ge {
    class Logger;
    extern Logger* mainLogger;

    class Logger {
    public:
        Logger(); // TODO: specify log file (default STDOUT), and format
        ~Logger();

        enum class Priority {
            TRACE, DEBUG, ERROR, WARNI, FATAL
        };

        struct Log {
            //std::chrono::time_point<std::chrono::high_resolution_clock> time_point; // TODO: Add platform time
            std::string raw_data;
            Priority priority;

            Log(const std::string& raw, Priority p);
        };

        void log(Priority p, const std::string& str);
        void emptyLogQueue();

    private:
        std::string format(const Log& log);

        std::queue<Log> m_queue;
    };

    void mainLog(Logger::Priority p, const std::string& parser,
                 const std::initializer_list<utility::StringFormat::ValidType>& t);
}

#define R8GE_LOG_TRACE(str, ...) r8ge::mainLog(r8ge::Logger::Priority::TRACE, str,{__VA_ARGS__})
#define R8GE_LOG_DEBUG(str, ...) r8ge::mainLog(r8ge::Logger::Priority::DEBUG, str,{__VA_ARGS__})
#define R8GE_LOG_WARNI(str, ...) r8ge::mainLog(r8ge::Logger::Priority::WARNI, str,{__VA_ARGS__})
#define R8GE_LOG_ERROR(str, ...) r8ge::mainLog(r8ge::Logger::Priority::ERROR, str,{__VA_ARGS__})
#define R8GE_LOG_FATAL(str, ...) r8ge::mainLog(r8ge::Logger::Priority::FATAL, str,{__VA_ARGS__})

//#define R8GE_LOG(...) R8GE_LOG_TRACE(__VA_ARGS__)z

#endif//!R8GE_LOGGER_H
