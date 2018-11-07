#ifndef PermissionsSetter_H
#define PermissionsSetter_H

#include <string>
#include "IFileInfoProvider.h"

class PermissionsSetter
{
  public:
    void SetPermissions(std::string fileLocation, std::string permissions, IFileInfoProvider* fileInfoProvider);
};

#endif