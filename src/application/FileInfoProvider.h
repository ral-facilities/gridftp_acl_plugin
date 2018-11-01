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
};

#endif