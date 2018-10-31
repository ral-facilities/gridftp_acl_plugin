#ifndef PermissionsReader_H
#define PermissionsReader_H

#include <string>
#include "IPermissionsReader.h"
using namespace std;

class PermissionsReader: public IPermissionsReader
{
  public:
    struct stat GetPermissions(string fileLocation);
};

#endif