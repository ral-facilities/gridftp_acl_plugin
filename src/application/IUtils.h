#ifndef IUtils_H
#define IUtils_H

#include <sys/stat.h>
#include <string>
#include <map>
#include <vector>
using namespace std;

class IUtils
{
  public:
    virtual ~IUtils() {}
    virtual std::map<std::string, std::string> SettingsStringToMap(std::string inputSettings) const = 0;
};

#endif