#ifndef ILogger_H
#define ILogger_H

#include <string>
using namespace std;

class ILogger
{

  public:
    virtual ~ILogger() {}
    virtual void Init(string logFileLocation, string logLevel) = 0;
    virtual void LogTrace(string message) const = 0;
    virtual void LogInfo(string message) const = 0;
    virtual void LogError(string message) const = 0;
};

#endif