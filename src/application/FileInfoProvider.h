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
    void SetMode(std::string fileLocation, int mode) const override;
    void SetUserAndGroupID(std::string fileLocation, int userID, int groupID) const override;
};

#endif