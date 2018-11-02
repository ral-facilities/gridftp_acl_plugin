#ifndef FileInfoProvider_H
#define FileInfoProvider_H

#include <sys/stat.h>
#include <string>
#include "IFileInfoProvider.h"

using namespace std;

class FileInfoProvider: public IFileInfoProvider
{
  public:
    struct stat GetPermissions(std::string fileLocation) const override;
    bool Exists(std::string fileLocation) const override;
    void SetPermissions(std::string fileLocation, std::string permissions) const override;
};

#endif