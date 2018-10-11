#ifndef Logger_H
#define Logger_H

#include <string>
#include <map>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "ILogger.h"
using namespace std;

class Logger: public ILogger
{
  public:
    void Init(string logFileLocation, string logLevel) override;
    void LogTrace(string message) const override;
    void LogInfo(string message) const override;
    void LogError(string message) const override;

  private:
    std::shared_ptr<spdlog::logger> logger;
    std::map<std::string, spdlog::level::level_enum> logLevelMap;
    void logMessage(const std::string& message, const spdlog::level::level_enum level) const;
};

#endif