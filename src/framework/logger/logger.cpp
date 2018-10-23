#include "logger.h"

void Logger::Init(string logFileLocation, string logLevel) 
{
    // Create the logger
    const auto logFiles = logFileLocation + "gridftp_acl_plugin.log";
    const auto rotatingFileSize = 10 * 1024 * 1024;
    const auto numberOfFiles = 3;
    logger = spdlog::rotating_logger_mt("gridftp_acl_plugin_logger", logFiles, rotatingFileSize, numberOfFiles);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S %z] [%l] %v ");

    // Setup up log level map
    logLevelMap["TRACE"] = spdlog::level::level_enum::trace;
    logLevelMap["DEBUG"] = spdlog::level::level_enum::debug;
    logLevelMap["INFO"] = spdlog::level::level_enum::info;
    logLevelMap["WARNING"] = spdlog::level::level_enum::warn;
    logLevelMap["ERROR"] = spdlog::level::level_enum::err;
    logLevelMap["FATAL"] = spdlog::level::level_enum::critical;

    transform(logLevel.begin(), logLevel.end(), logLevel.begin(), ::toupper);
    spdlog::set_level(logLevelMap[logLevel]);
}

void Logger::LogError(string message) const {
  logMessage(message, spdlog::level::level_enum::err);
}

void Logger::LogInfo(string message) const {
  logMessage(message, spdlog::level::level_enum::info);
}

void Logger::LogTrace(string message) const {
  logMessage(message, spdlog::level::level_enum::trace);
}

void Logger::logMessage(const std::string& message, const spdlog::level::level_enum level) const {
    logger->log(level, message);
}
