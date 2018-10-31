#ifndef IPermissionsReader_H
#define IPermissionsReader_H

#include <sys/stat.h>
#include <string>
using namespace std;

class IPermissionsReader
{
  public:
    struct stat GetPermissions(std::string fileLocation);
};

#endif