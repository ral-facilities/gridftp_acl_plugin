#include "FileInfoProvider.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "Utils.h"

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
    // int chmod(const char *path, mode_t mode);
    // chmod((char*)"/tmp/test.txt", 100777);
    // chmod((char*)"/tmp/test.txt", S_IRWXU);
    // chmod((char*)"/tmp/test.txt", 16895);
    Utils utils;
    char * fileCharArray = utils.StringToCharArray(fileLocation);
    return (chmod(fileCharArray, mode) == 0);
}

bool FileInfoProvider::SetUserAndGroupID(std::string fileLocation, int userID, int groupID) const
{
    Utils utils;
    char * fileCharArray = utils.StringToCharArray(fileLocation);
    return (chown(fileCharArray, userID, groupID) == 0);
}