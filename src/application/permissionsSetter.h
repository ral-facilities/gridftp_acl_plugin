#ifndef PermissionsSetter_H
#define PermissionsSetter_H

#include <map>
#include <string>
#include "IFileInfoProvider.h"
#include "IUtils.h"

class PermissionsSetter
{
  public:
    void SetPermissions(std::string fileLocation, std::string permissions, IUtils* utils, IFileInfoProvider* fileInfoProvider);
};

#endif