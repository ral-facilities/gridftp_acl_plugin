#ifndef PermissionsReader_H
#define PermissionsReader_H

#include <string>
#include "IFileInfoProvider.h"
using namespace std;

class PermissionsReader
{
  public:
    std::string GetPermissions(std::string fileLocation, IFileInfoProvider* fileInfoProvider);
};

#endif