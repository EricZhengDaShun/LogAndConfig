#include "Config/Log.hpp"
#include "ConfigLoader/ConfigLoader.hpp"

#include "spdlog/common.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <exception>
#include <string>

#include <cstdlib>

void settingSpdlog(const LogAndConfig::Config::Log& log)
{
    spdlog::level::level_enum level = spdlog::level::trace;
    if (log.level == "trace") {
        level = spdlog::level::trace;
    } else if (log.level == "debug") {
        level = spdlog::level::debug;
    } else if (log.level == "info") {
        level = spdlog::level::info;
    } else if (log.level == "warn") {
        level = spdlog::level::warn;
    } else if (log.level == "err") {
        level = spdlog::level::err;
    } else if (log.level == "critical") {
        level = spdlog::level::critical;
    }

    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(level);
    consoleSink->set_pattern("[Log] [%^%l%$] %v");

    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log.path, 1048576 * log.maxSizeMB, log.fileNum);
    fileSink->set_level(level);

    auto multiSink = std::make_shared<spdlog::logger>("Log");
    multiSink->sinks().push_back(consoleSink);
    multiSink->sinks().push_back(fileSink);

    spdlog::set_default_logger(multiSink);
    spdlog::set_level(level);

    return;
}

int main()
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    using namespace LogAndConfig;

    ConfigLoader configLoader;
    try {
        if (!configLoader.loadFile("config.json")) {
            spdlog::error("load config file fail!");
            return EXIT_FAILURE;
        }

    } catch (std::exception& e) {
        spdlog::error("ConfigLoader exception: {}", e.what());
        return EXIT_FAILURE;
    }

    LogAndConfig::Config::Log log = configLoader.log();
    settingSpdlog(log);

    spdlog::info("Start!");

    return EXIT_SUCCESS;
}
