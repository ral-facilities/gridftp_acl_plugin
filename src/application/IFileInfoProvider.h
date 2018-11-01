#ifndef IFileInfoProvider_H
#define IFileInfoProvider_H

#include <sys/stat.h>
#include <string>
using namespace std;

class IFileInfoProvider
{
  public:
    virtual ~IFileInfoProvider() {}
    virtual struct stat GetPermissions(std::string fileLocation) const = 0;
};

#endif