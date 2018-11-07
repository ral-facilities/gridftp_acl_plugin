#ifndef Utils_H
#define Utils_H
#include <string>
#include <vector>
#include <map>

class Utils
{
  public:
    char* StringToCharArray(std::string input);
    std::vector<std::string> StringSplitter(std::string input, std::string delimiter1, std::string delimiter2);
    std::map<std::string, std::string> TokensToMap(std::vector<std::string> tokens);
};

#endif
