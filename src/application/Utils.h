#ifndef Utils_H
#define Utils_H
#include <string>
#include <vector>
#include <map>
#include "IUtils.h"

class Utils: public IUtils
{
  public:
    std::map<std::string, std::string> SettingsStringToMap(std::string inputSettings) const override;
  private:
    std::vector<std::string> StringSplitter(std::string input, char delimiter) const;
};

#endif
