#include "../r8gepch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace r8ge {
     namespace global {
        Logger* logger = nullptr;
    }

    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    Logger::Logger()
    {
        m_running = true;
        m_thread = std::thread(&Logger::logLoop, this);
        init();
    }


    Logger::~Logger()
    {
        m_running = false;
        m_thread.join();
    }

    void Logger::init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("R8GE.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_Logger = std::make_shared<spdlog::logger>("R8GE", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_Logger);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }

    void Logger::logLoop()
    {
        while(m_running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
