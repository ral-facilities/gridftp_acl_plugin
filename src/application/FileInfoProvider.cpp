#include "FileInfoProvider.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "IUtils.h"

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

bool FileInfoProvider::SetMode(std::string fileLocation, int mode) const
{
    return (chmod(fileLocation.c_str(), mode) == 0);
}

bool FileInfoProvider::SetUserAndGroupID(std::string fileLocation, int userID, int groupID) const
{
    return (chown(fileLocation.c_str(), userID, groupID) == 0);
}