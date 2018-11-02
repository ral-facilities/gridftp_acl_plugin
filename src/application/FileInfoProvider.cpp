#include "FileInfoProvider.h"
#include <stdexcept>
#include <iostream>

struct stat FileInfoProvider::GetPermissions(std::string fileLocation) const
{
    struct stat buf;
    stat(fileLocation.c_str(), &buf);
    return buf;
}

bool FileInfoProvider::Exists(std::string fileLocation) const
{
    struct stat buf;
    return (stat(fileLocation.c_str(), &buf) == 0);
}